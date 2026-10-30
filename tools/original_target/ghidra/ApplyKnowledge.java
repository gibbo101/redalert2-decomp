// Feeds recovered knowledge back into the decompiler. Analysis hypotheses only.
// Arg 0: JSON lines {entry, symbol}: accepted functions; each MSVC mangled name is
//        demangled and applied (name, namespace, parameters, return, convention).
// Arg 1: C header of flat class structs (render_layouts output) or "-".
// Arg 2: JSON object {"Class": ["hexentry", ...]}: unrecovered members to move into
//        the class as __thiscall; each class's this-struct takes the parsed layout.
// Arg 3: output directory; arg 4: "named" or "fun" (rename accepted functions back
//        to FUN_<entry> after applying signatures, for seed tools that bind FUN_).
// Decompiles only the entries of arg 2 into <out>/decompiled and <out>/functions.jsonl.
// @category RA2Private
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.app.util.cparser.C.CParser;
import ghidra.app.util.demangler.*;
import ghidra.app.util.demangler.microsoft.*;
import ghidra.app.util.NamespaceUtils;
import ghidra.program.model.address.*;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import com.google.gson.*;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.io.*;
import java.util.*;

public class ApplyKnowledge extends GhidraScript {
    public void run() throws Exception {
        String[] a = getScriptArgs();
        Path out = Paths.get(a[3]);
        Files.createDirectories(out.resolve("decompiled"));
        boolean fun = a.length > 4 && a[4].equals("fun");
        Map<String, Object> summary = new LinkedHashMap<>();

        // 1. Accepted symbols.
        MicrosoftDemangler demangler = new MicrosoftDemangler();
        int applied = 0, failed = 0;
        List<Address> accepted = new ArrayList<>();
        try (BufferedReader r = Files.newBufferedReader(Paths.get(a[0]))) {
            String line;
            while ((line = r.readLine()) != null && !monitor.isCancelled()) {
                JsonObject o = JsonParser.parseString(line).getAsJsonObject();
                Address addr = toAddr(o.get("entry").getAsLong());
                String mangled = o.get("symbol").getAsString();
                try {
                    if (getFunctionAt(addr) == null) createFunction(addr, null);
                    MicrosoftDemanglerOptions opts = demangler.createDefaultOptions();
                    opts.setApplySignature(true);
                    opts.setApplyCallingConvention(true);
                    opts.setDoDisassembly(false);
                    MangledContext ctx = demangler.createMangledContext(mangled, opts, currentProgram, addr);
                    DemangledObject obj = demangler.demangle(ctx);
                    if (obj != null && obj.applyUsingContext(monitor)) { applied++; accepted.add(addr); }
                    else failed++;
                } catch (Exception e) { failed++; }
            }
        }
        summary.put("demangled_applied", applied);
        summary.put("demangled_failed", failed);

        // 2. Layouts.
        DataTypeManager dtm = currentProgram.getDataTypeManager();
        Map<String, DataType> parsed = new HashMap<>();
        if (!a[1].equals("-")) {
            CParser parser = new CParser(dtm, true, null);
            parser.parse(Files.readString(Paths.get(a[1])));
            for (DataType dt : parser.getComposites().values()) parsed.put(dt.getName(), dt);
        }
        summary.put("parsed_structs", parsed.size());

        // 3. Members.
        JsonObject members = JsonParser.parseString(Files.readString(Paths.get(a[2]))).getAsJsonObject();
        List<Function> targets = new ArrayList<>();
        SymbolTable st = currentProgram.getSymbolTable();
        for (String cname : members.keySet()) {
            Namespace ns = st.getNamespace(cname, currentProgram.getGlobalNamespace());
            GhidraClass cls;
            if (ns == null) cls = st.createClass(currentProgram.getGlobalNamespace(), cname, SourceType.USER_DEFINED);
            else if (ns instanceof GhidraClass) cls = (GhidraClass) ns;
            else cls = NamespaceUtils.convertNamespaceToClass(ns);
            Structure s = VariableUtilities.findOrCreateClassStruct(cls, dtm);
            DataType layout = parsed.get(cname);
            if (layout instanceof Structure) {
                // The demangler may have made its own placeholder: fill every same-named struct.
                List<DataType> same = new ArrayList<>();
                dtm.findDataTypes(cname, same);
                same.add(s);
                for (DataType d : same)
                    if (d instanceof Structure && d != layout) ((Structure) d).replaceWith(layout);
                summary.put("struct_" + cname, same.size() + " filled, size " + s.getLength());
            }
            for (JsonElement e : members.getAsJsonArray(cname)) {
                Function f = getFunctionAt(toAddr(Long.parseUnsignedLong(e.getAsString(), 16)));
                if (f == null) continue;
                f.setParentNamespace(cls);
                f.setCallingConvention("__thiscall");
                targets.add(f);
            }
        }

        // 4. Seed-tool view: accepted functions keep signatures, lose names.
        if (fun) {
            for (Address addr : accepted) {
                Function f = getFunctionAt(addr);
                if (f == null) continue;
                try {
                    f.setParentNamespace(currentProgram.getGlobalNamespace());
                    f.setName(String.format("FUN_%08x", addr.getOffset()), SourceType.ANALYSIS);
                } catch (Exception e) { /* keep the demangled name */ }
            }
        }

        // 5. Decompile the targets only.
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        Gson gson = new Gson();
        try (BufferedWriter fw = Files.newBufferedWriter(out.resolve("functions.jsonl"))) {
            for (Function f : targets) {
                DecompileResults dr = di.decompileFunction(f, 60, monitor);
                String name = String.format("%08x.c", f.getEntryPoint().getOffset());
                if (dr.decompileCompleted() && dr.getDecompiledFunction() != null)
                    Files.writeString(out.resolve("decompiled").resolve(name), dr.getDecompiledFunction().getC(),
                                      StandardCharsets.UTF_8);
                Map<String, Object> row = new LinkedHashMap<>();
                row.put("entry", f.getEntryPoint().toString());
                row.put("name", f.getName());
                row.put("signature", f.getSignature().toString());
                row.put("calling_convention", f.getCallingConventionName());
                row.put("completed", dr.decompileCompleted());
                fw.write(gson.toJson(row));
                fw.newLine();
            }
        }
        di.dispose();
        Files.writeString(out.resolve("apply-summary.json"), gson.toJson(summary));
        println("APPLY_KNOWLEDGE " + gson.toJson(summary));
    }
}
