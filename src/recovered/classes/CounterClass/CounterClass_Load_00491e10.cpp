HRESULT CounterClass::Load(IStream *stream) {
 new(this) CounterClass;
 int count;
 HRESULT result=stream->Read(&count,4,0);
 if (FAILED(result)) return result;
 if (!Resize(count)) return 8;
 for(int i=0;i<count;++i) { result=stream->Read(&Vector[i],4,0);if(FAILED(result))return result; }
 return 0;
}
