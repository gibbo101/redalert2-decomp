#!/bin/zsh
# Dry-run acceptance: run the real accept_sources.py for each plan inside a
# throwaway git worktree of HEAD with proposed shared headers installed, so a
# worker can check a header set plus plans exactly as the owner's acceptance
# will, without touching the main tree's src/ or manifests/.
#
#   tools/original_target/check_plans.sh NAME HEADER_DIR PLAN...
#
# HEADER_DIR holds proposed *.hpp copies (a `shared/` subdirectory is also
# accepted); they are copied over the worktree's src/shared. Plans are
# accepted in the order given, so later plans see earlier ones. Results go to
# build/check/NAME/results.txt; the worktree is build/check/NAME/wt and is
# removed on the next run with the same NAME.
set -eu
REPO=${0:A:h:h:h}
NAME=$1; HEADERS=$2; shift 2
PY=${RA2_PYTHON:-$REPO/private/matching-pilot/20261020T123117Z/env/bin/python}
CONFIG=${RA2_CONFIG:-$REPO/private/original-target.interactive.json}
BASE=$REPO/build/check/$NAME
WT=$BASE/wt
cd $REPO
if [ -d $WT ]; then git worktree remove --force $WT; fi
rm -rf $BASE; mkdir -p $BASE
git worktree add --detach $WT HEAD >/dev/null
# The main tree's current src/ and manifests/ (including uncommitted
# accepted work) are the baseline.
rsync -a --delete $REPO/src/ $WT/src/
# Acceptance rewrites the manifest in place; retry until a complete copy parses.
for i in 1 2 3 4 5 6 7 8 9 10; do
  rsync -a --delete $REPO/manifests/ $WT/manifests/
  $PY -c "import sys; sys.path.insert(0, sys.argv[1]+'/tools/original_target'); import catalog_io; catalog_io.load(catalog_io.locate(sys.argv[1]), references=False)" $WT 2>/dev/null && break
  sleep 3
done
# Acceptance writes population mappings into private/original-target.*.json
# and composite inventory passes into the inventory folder, so the worktree
# gets its own copies of those; everything else in private/ is linked.
mkdir -p $WT/private
for f in $REPO/private/*(N) $REPO/private/.*(N); do
  case ${f:t} in
    original-target.*.json) cp $f $WT/private/ ;;
    original-target-20261020) ;;
    *) ln -s $f $WT/private/${f:t} ;;
  esac
done
OT=$REPO/private/original-target-20261020
mkdir -p $WT/private/${OT:t}/inventory
for f in $OT/*(N); do
  [ ${f:t} = inventory ] || ln -s $f $WT/private/${OT:t}/${f:t}
done
for f in $OT/inventory/*(N); do ln -s $f $WT/private/${OT:t}/inventory/${f:t}; done
mkdir -p $WT/build && ln -s $REPO/build/class-work $WT/build/class-work
[ -d $HEADERS/shared ] && HEADERS=$HEADERS/shared
cp $HEADERS/*.hpp $WT/src/shared/
for plan in "$@"; do
  n=${plan:t:r}
  print "=== $plan" >> $BASE/results.txt
  (cd $WT && $PY -B tools/original_target/accept_sources.py --config $WT/private/${CONFIG:t} \
      --output $WT/build/accept-$n $REPO/$plan 2>&1 |
   grep -E '"candidates"|"accepted"|"missed"|"error"|refus|plan replaces|rror' | head -6) >> $BASE/results.txt || true
done
# Keep each plan's reports and compile logs, then drop the worktree (each is
# several GB).
for d in $WT/build/accept-*(N/); do
  mkdir -p $BASE/${d:t}
  (cd $d && find . \( -name '*.json' -o -name '*.log' \) -print0 | cpio -0pdm $BASE/${d:t} 2>/dev/null)
done
git worktree remove --force $WT
print DONE >> $BASE/results.txt
cat $BASE/results.txt
