// Applies repair_bodies.py output: clears the listed wrong no-return flags,
// disassembles the bytes Ghidra skipped after calls to them, and sets each
// repaired function's body to its single merged range. Run with -noanalysis
// so nothing else changes before export. Args: repairs.json summary.json
// @category RA2Private
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import com.google.gson.*;
import java.nio.file.*;
import java.util.*;

public class RepairBodies extends GhidraScript {
    public void run() throws Exception {
        String[] args = getScriptArgs();
        JsonObject input = JsonParser.parseString(Files.readString(Paths.get(args[0]))).getAsJsonObject();
        int cleared = 0, repaired = 0, failed = 0;
        for (JsonElement element : input.getAsJsonArray("wrong_noreturn")) {
            Function function = getFunctionAt(toAddr(Long.parseUnsignedLong(element.getAsString(), 16)));
            if (function != null && function.hasNoReturn()) { function.setNoReturn(false); cleared++; }
        }
        List<String> failures = new ArrayList<>();
        for (JsonElement element : input.getAsJsonArray("repairs")) {
            JsonObject repair = element.getAsJsonObject();
            Address entry = toAddr(Long.parseUnsignedLong(repair.get("entry").getAsString(), 16));
            Address start = toAddr(Long.parseUnsignedLong(repair.get("start").getAsString(), 16));
            Address end = toAddr(Long.parseUnsignedLong(repair.get("end_inclusive").getAsString(), 16));
            try {
                Address at = start;
                while (at.compareTo(end) <= 0) {
                    Instruction instruction = getInstructionAt(at);
                    if (instruction == null) {
                        clearListing(at, at);
                        disassemble(at);
                        instruction = getInstructionAt(at);
                        if (instruction == null) throw new Exception("no instruction at " + at);
                    }
                    instruction.clearFallThroughOverride();
                    instruction.setFlowOverride(ghidra.program.model.listing.FlowOverride.NONE);
                    at = instruction.getMaxAddress().next();
                }
                Function function = getFunctionAt(entry);
                // Functions starting inside the merged range were tails of this body.
                FunctionIterator inside = currentProgram.getFunctionManager().getFunctions(new AddressSet(start.next(), end), true);
                for (Function other : inside) if (!other.getEntryPoint().equals(entry)) removeFunction(other);
                function.setBody(new AddressSet(start, end));
                repaired++;
            } catch (Exception e) {
                failed++; failures.add(repair.get("entry").getAsString() + ": " + e);
            }
        }
        Map<String, Object> summary = new LinkedHashMap<>();
        summary.put("cleared_noreturn", cleared);
        summary.put("repaired", repaired);
        summary.put("failed", failed);
        summary.put("failures", failures.subList(0, Math.min(50, failures.size())));
        Files.writeString(Paths.get(args[1]), new Gson().toJson(summary));
        println("REPAIRBODIES " + new Gson().toJson(summary));
    }
}
