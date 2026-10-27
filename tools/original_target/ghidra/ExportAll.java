// Private original-binary research only. Whole-program auto-analysis hypotheses.
// @category RA2Private
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import com.google.gson.Gson;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.io.*;
import java.util.*;

public class ExportAll extends GhidraScript {
  Gson gson=new Gson();
  String addr(Address a) {return a==null?null:a.toString();}
  public void run() throws Exception {
    Path out=Paths.get(getScriptArgs()[0]); Files.createDirectories(out.resolve("decompiled"));
    long begin=System.nanoTime(); int total=0,external=0,thunks=0,noncontiguous=0;
    AddressSet bodies=new AddressSet();
    try(BufferedWriter fw=Files.newBufferedWriter(out.resolve("functions.jsonl"));
        BufferedWriter iw=Files.newBufferedWriter(out.resolve("instructions.jsonl"))) {
      FunctionIterator fit=currentProgram.getFunctionManager().getFunctions(true);
      while(fit.hasNext()&&!monitor.isCancelled()) {
        Function f=fit.next(); Map<String,Object> row=new LinkedHashMap<>();
        row.put("entry",addr(f.getEntryPoint())); row.put("name",f.getName()); row.put("qualified_name",f.getName(true));
        row.put("signature",f.getSignature().toString()); row.put("calling_convention",f.getCallingConventionName());
        row.put("external",f.isExternal());row.put("thunk",f.isThunk());row.put("noreturn",f.hasNoReturn());
        row.put("symbol_source",f.getSymbol().getSource().toString()); row.put("signature_source",f.getSignatureSource().toString());
        row.put("status","ghidra_autoanalysis_hypothesis_not_independently_verified");
        row.put("confidence","analysis-derived bounds; no next-alignment extent inference; not strict byte-match acceptance");
        row.put("body_bytes",f.getBody().getNumAddresses());
        List<Map<String,Object>> ranges=new ArrayList<>(); AddressRangeIterator rit=f.getBody().getAddressRanges();
        while(rit.hasNext()) {AddressRange r=rit.next();Map<String,Object> rr=new LinkedHashMap<>(); rr.put("start",addr(r.getMinAddress()));rr.put("end_inclusive",addr(r.getMaxAddress()));rr.put("length",r.getLength());
          try {byte[] b=new byte[(int)r.getLength()];currentProgram.getMemory().getBytes(r.getMinAddress(),b);StringBuilder hex=new StringBuilder();for(byte v:b)hex.append(String.format("%02x",v&255));rr.put("bytes_hex",hex.toString());}catch(Exception e){rr.put("read_error",e.toString());}
          ranges.add(rr);
        }
        row.put("ranges",ranges);row.put("contiguous",ranges.size()==1);if(ranges.size()>1)noncontiguous++;
        int nins=0;InstructionIterator ins=currentProgram.getListing().getInstructions(f.getBody(),true);
        while(ins.hasNext()) {Instruction i=ins.next();nins++;Map<String,Object> ir=new LinkedHashMap<>();ir.put("function_entry",addr(f.getEntryPoint()));ir.put("address",addr(i.getAddress()));ir.put("length",i.getLength());ir.put("text",i.toString());ir.put("flow_type",i.getFlowType().toString());List<String> flows=new ArrayList<>();for(Address a:i.getFlows())flows.add(addr(a));ir.put("flows",flows);ir.put("fallthrough",addr(i.getFallThrough()));iw.write(gson.toJson(ir));iw.newLine();}
        row.put("instruction_count",nins);
        List<Map<String,Object>> refs=new ArrayList<>();ReferenceIterator refit=currentProgram.getReferenceManager().getReferencesTo(f.getEntryPoint());while(refit.hasNext()){Reference r=refit.next();Map<String,Object> rr=new LinkedHashMap<>();rr.put("from",addr(r.getFromAddress()));rr.put("type",r.getReferenceType().toString());refs.add(rr);}row.put("entry_references",refs);
        Function tf=f.isThunk()?f.getThunkedFunction(true):null;row.put("thunk_target",tf==null?null:addr(tf.getEntryPoint()));
        fw.write(gson.toJson(row));fw.newLine();if(!f.isExternal())bodies.add(f.getBody());total++;if(f.isExternal())external++;if(f.isThunk())thunks++;
      }
    }
    Map<String,Object> summary=new LinkedHashMap<>();summary.put("function_count",total);summary.put("external_count",external);summary.put("thunk_count",thunks);summary.put("noncontiguous_count",noncontiguous);summary.put("union_body_bytes",bodies.getNumAddresses());summary.put("metadata_seconds",(System.nanoTime()-begin)/1e9);summary.put("automatic_analysis",true);
    List<Map<String,Object>> blocks=new ArrayList<>();try(BufferedWriter gaps=Files.newBufferedWriter(out.resolve("unassigned-executable.jsonl"))) {for(MemoryBlock b:currentProgram.getMemory().getBlocks()){Map<String,Object> bl=new LinkedHashMap<>();bl.put("name",b.getName());bl.put("start",addr(b.getStart()));bl.put("end_inclusive",addr(b.getEnd()));bl.put("size",b.getSize());bl.put("execute",b.isExecute());bl.put("initialized",b.isInitialized());blocks.add(bl);if(b.isExecute()){AddressSet remaining=new AddressSet(b.getStart(),b.getEnd());remaining.delete(bodies);AddressRangeIterator ri=remaining.getAddressRanges();while(ri.hasNext()){AddressRange r=ri.next();Map<String,Object> row=new LinkedHashMap<>();row.put("start",addr(r.getMinAddress()));row.put("end_inclusive",addr(r.getMaxAddress()));row.put("length",r.getLength());row.put("classification","outside_discovered_function_bodies_unknown_code_data_padding");gaps.write(gson.toJson(row));gaps.newLine();}}}}
    summary.put("memory_blocks",blocks);Files.writeString(out.resolve("inventory-summary.json"),gson.toJson(summary));Files.writeString(out.resolve("METADATA_READY"),"Metadata exported; decompilation in progress.\n");println("METADATA_READY functions="+total);
    DecompInterface di=new DecompInterface();di.openProgram(currentProgram);int ok=0,failed=0;
    try(BufferedWriter statuses=Files.newBufferedWriter(out.resolve("decompilation-status.jsonl"))) {FunctionIterator fi=currentProgram.getFunctionManager().getFunctions(true);while(fi.hasNext()&&!monitor.isCancelled()){Function f=fi.next();if(f.isExternal())continue;Map<String,Object> row=new LinkedHashMap<>();row.put("entry",addr(f.getEntryPoint()));long st=System.nanoTime();try{DecompileResults dr=di.decompileFunction(f,20,monitor);boolean done=dr.decompileCompleted()&&dr.getDecompiledFunction()!=null;row.put("completed",done);row.put("error",dr.getErrorMessage());if(done){String name=f.getEntryPoint().toString().replace(':','_')+".c";Files.writeString(out.resolve("decompiled").resolve(name),dr.getDecompiledFunction().getC(),StandardCharsets.UTF_8);row.put("file","decompiled/"+name);ok++;}else failed++;}catch(Exception e){row.put("completed",false);row.put("error",e.toString());failed++;}row.put("seconds",(System.nanoTime()-st)/1e9);statuses.write(gson.toJson(row));statuses.newLine();if((ok+failed)%100==0){statuses.flush();println("DECOMPILE "+(ok+failed)+" ok="+ok+" failed="+failed);}}}
    di.dispose();summary.put("decompiled_ok",ok);summary.put("decompiled_failed",failed);summary.put("total_export_seconds",(System.nanoTime()-begin)/1e9);Files.writeString(out.resolve("inventory-summary.json"),gson.toJson(summary));Files.writeString(out.resolve("EXPORT_COMPLETE"),gson.toJson(summary));println("EXPORT_COMPLETE "+gson.toJson(summary));
  }
}
