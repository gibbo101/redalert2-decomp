// Private supplement: explicit imported external function table, symbol and defined-data metadata.
// @category RA2Private
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import com.google.gson.Gson;
import java.nio.file.*;
import java.io.*;
import java.util.*;
public class ExportSupplement extends GhidraScript {
 public void run() throws Exception {
  Path out=Paths.get(getScriptArgs()[0]); Gson gson=new Gson(); int nf=0,ns=0,nd=0;
  try(BufferedWriter w=Files.newBufferedWriter(out.resolve("external-functions.jsonl"))) {FunctionIterator fi=currentProgram.getFunctionManager().getExternalFunctions();while(fi.hasNext()){Function f=fi.next();Map<String,Object> r=new LinkedHashMap<>();r.put("entry",f.getEntryPoint().toString());r.put("name",f.getName(true));r.put("signature",f.getSignature().toString());r.put("calling_convention",f.getCallingConventionName());r.put("external",true);r.put("thunk",f.isThunk());r.put("status","import_metadata_no_local_function_body");r.put("symbol_source",f.getSymbol().getSource().toString());w.write(gson.toJson(r));w.newLine();nf++;}}
  try(BufferedWriter w=Files.newBufferedWriter(out.resolve("symbols.jsonl"))){SymbolIterator si=currentProgram.getSymbolTable().getAllSymbols(true);while(si.hasNext()){Symbol s=si.next();Map<String,Object> r=new LinkedHashMap<>();r.put("address",s.getAddress().toString());r.put("name",s.getName(true));r.put("type",s.getSymbolType().toString());r.put("source",s.getSource().toString());r.put("external",s.isExternal());w.write(gson.toJson(r));w.newLine();ns++;}}
  try(BufferedWriter w=Files.newBufferedWriter(out.resolve("defined-data.jsonl"))){DataIterator di=currentProgram.getListing().getDefinedData(true);while(di.hasNext()){Data d=di.next();Map<String,Object> r=new LinkedHashMap<>();r.put("address",d.getAddress().toString());r.put("length",d.getLength());r.put("datatype",d.getDataType().getName());r.put("status","ghidra_defined_data_not_independent_verification");w.write(gson.toJson(r));w.newLine();nd++;}}
  Map<String,Object> sum=new LinkedHashMap<>();sum.put("external_functions",nf);sum.put("symbols",ns);sum.put("defined_data_items",nd);Files.writeString(out.resolve("supplement-summary.json"),gson.toJson(sum));println("SUPPLEMENT_COMPLETE "+gson.toJson(sum));
 }
}
