// Private second-pass discovery only; seeds from actual data pointers, not independently verified functions.
// @category RA2Private
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import com.google.gson.*;
import java.nio.file.*;
import java.io.*;
import java.util.*;
public class SeedPointers extends GhidraScript {
 public void run() throws Exception {
  String[] args=getScriptArgs();Gson gson=new Gson();int made=0,refused=0,already=0;long start=System.nanoTime();
  try(BufferedReader br=Files.newBufferedReader(Paths.get(args[0]));BufferedWriter w=Files.newBufferedWriter(Paths.get(args[1]))) {
   String line;while((line=br.readLine())!=null&&!monitor.isCancelled()) {
    JsonObject seed=JsonParser.parseString(line).getAsJsonObject();String target=seed.get("target").getAsString();Address a=toAddr(Long.parseUnsignedLong(target,16));Map<String,Object> row=new LinkedHashMap<>();row.put("target",target);row.put("evidence",seed);row.put("confidence","pointer-target automatic discovery; not independently verified entry/bounds or source recovery acceptance");
    Function at=getFunctionAt(a),containing=getFunctionContaining(a);Instruction ins=currentProgram.getListing().getInstructionContaining(a);Data data=currentProgram.getListing().getDefinedDataContaining(a);
    if(at!=null){row.put("status","already_function");already++;}
    else if(containing!=null){row.put("status","refused_existing_function_interior");row.put("containing_entry",containing.getEntryPoint().toString());refused++;}
    else if(ins!=null&&!ins.getAddress().equals(a)){row.put("status","refused_existing_instruction_interior");refused++;}
    else if(data!=null){row.put("status","refused_defined_data");row.put("datatype",data.getDataType().getName());refused++;}
    else {try{boolean dis=disassemble(a);Function f=dis?createFunction(a,"PTR_"+target):null;if(f==null){row.put("status","refused_disassembly_or_function_creation");refused++;}else{row.put("status","created_analysis_hypothesis");row.put("initial_body_bytes",f.getBody().getNumAddresses());made++;}}catch(Exception e){row.put("status","refused_exception");row.put("error",e.toString());refused++;}}
    w.write(gson.toJson(row));w.newLine();if((made+refused+already)%500==0){w.flush();println("SEEDS "+(made+refused+already)+" created="+made+" refused="+refused);}
   }
  }
  Map<String,Object> summary=new LinkedHashMap<>();summary.put("created_hypotheses",made);summary.put("refused",refused);summary.put("already_function",already);summary.put("seconds",(System.nanoTime()-start)/1e9);Files.writeString(Paths.get(args[1]+".summary.json"),gson.toJson(summary));println("SEED_COMPLETE "+gson.toJson(summary));
 }
}
