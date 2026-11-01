// static FootClass * __fastcall _Create_Group(TeamTypeClass *teamtype) -- 0x00639DA0 (TS reinf.cpp)
// Creates a team of the type and its task force's objects; returns the first transport with the
// others loaded into it, or the chain of objects when there is no transport.
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"
#include "shared/foot.hpp"
// @ref ?Unknown_007134E0@UnknownTechnoPair@@QAEX_N@Z=007134e0

FootClass * __fastcall _Create_Group(TeamTypeClass *teamtype)
{
    TeamClass *team = new TeamClass(teamtype, teamtype->Owner, 0);
    if (team != 0) {
        team->IsForcedActive = true;
        team->IsUnderStrength = false;
    }

    bool hasunload = false;
    ScriptTypeClass *script = teamtype->Script;
    int count = script->MissionCount;
    for (int tm = 0; tm < count; tm++) {
        ScriptMissionClass mission = script->MissionList[tm];
        if (mission.Mission == 8) {
            hasunload = true;
            break;
        }
    }

    bool has_air_transport = team->unknown_func_6bd810();

    FootClass *transport = 0;
    FootClass *object = 0;
    for (int index = 0; index < teamtype->TaskForce->CountEntries; index++) {
        TechnoTypeClass *tclass = teamtype->TaskForce->Entries[index].Type;

        for (int sub = 0; sub < teamtype->TaskForce->Entries[index].Amount; sub++) {
            unknown_a40774++;
            FootClass *temp = (FootClass *)tclass->unknown_slot35(teamtype->Owner);
            unknown_a40774--;

            if (temp != 0) {

                if (tclass->Storage > 0 && teamtype->Full) {
                    temp->unknown_294.Add_Amount(tclass->Storage, 0);
                }

                switch (teamtype->VeteranLevel) {
                    case 0:
                        temp->unknown_118.Unknown_007134E0(true);
                        break;
                    case 1:
                        break;
                    case 2:
                        temp->unknown_118.unknown_713520(true);
                        break;
                    case 3:
                        temp->unknown_118.Unknown_00713550(true);
                        break;
                }

                if (team != 0) {
                    unknown_a40774++;
                    team->unknown_func_6b8cc0(temp);
                    unknown_a40774--;
                    temp->unknown_579 = true;
                }

                bool transporter = false;
                if (tclass->Passengers > 0 && teamtype->Full) {
                    if (has_air_transport) {
                        if (temp->Kind_Of() == 2) {
                            transporter = true;
                        } else {
                            transporter = false;
                        }
                    } else {
                        if (temp->Kind_Of() == 1) {
                            transporter = true;
                        } else {
                            transporter = false;
                        }
                    }
                }

                if (transporter) {
                    temp->unknown_30 = transport;
                    transport = temp;
                } else {
                    temp->unknown_30 = object;
                    object = temp;
                }
            }
        }
    }

    if (transport != 0 && object != 0 && teamtype->Full) {
        transport->Cargo.Unknown_00468960(object);

        if (hasunload && transport->Kind_Of() == 2) {
            transport->unknown_32c = true;
        }
    }

    if (transport == 0 && object == 0) {
        if (team != 0) delete team;
        return 0;
    }

    if (transport == 0) {
        return object;
    }

    return transport;
}
