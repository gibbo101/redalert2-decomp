// Clears wrong no-return flags and repairs the bodies they truncated.
// Arg 0: JSON array of hex entries whose bodies contain returns. For each:
// clear noReturn, restore fall-through after every call to it, disassemble
// the fall-through code, and recompute each calling function's body.
// Arg 1: output JSON summary. Analysis hypotheses only, like every pass.
// @category RA2Private
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import com.google.gson.*;
import java.nio.file.*;
import java.util.*;

public class FixNoReturn extends GhidraScript {
    public void run() throws Exception {
        String[] args = getScriptArgs();
        JsonArray entries = JsonParser.parseString(Files.readString(Paths.get(args[0]))).getAsJsonArray();
        Set<Function> callers = new LinkedHashSet<>();
        int cleared = 0, sites = 0;
        for (JsonElement element : entries) {
            Address target = toAddr(Long.parseUnsignedLong(element.getAsString(), 16));
            Function function = getFunctionAt(target);
            if (function == null) continue;
            if (function.hasNoReturn()) { function.setNoReturn(false); cleared++; }
            for (Reference ref : getReferencesTo(target)) {
                if (!ref.getReferenceType().isCall()) continue;
                Instruction call = getInstructionAt(ref.getFromAddress());
                if (call == null) continue;
                call.setFlowOverride(FlowOverride.NONE);
                call.clearFallThroughOverride();
                Address next = call.getMaxAddress().next();
                if (next != null && getInstructionAt(next) == null) disassemble(next);
                Function caller = getFunctionContaining(call.getAddress());
                if (caller != null) callers.add(caller);
                sites++;
            }
        }
        int fixed = 0;
        for (Function caller : callers) {
            if (CreateFunctionCmd.fixupFunctionBody(currentProgram, caller, monitor)) fixed++;
        }
        Map<String, Object> summary = new LinkedHashMap<>();
        summary.put("cleared_noreturn", cleared);
        summary.put("call_sites", sites);
        summary.put("callers", callers.size());
        summary.put("bodies_recomputed", fixed);
        Files.writeString(Paths.get(args[1]), new Gson().toJson(summary));
        println("FIXNORETURN " + new Gson().toJson(summary));
    }
}
