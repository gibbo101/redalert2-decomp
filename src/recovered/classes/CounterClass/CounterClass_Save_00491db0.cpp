HRESULT CounterClass::Save(IStream *stream) {
 int count=VectorMax;
 HRESULT result=stream->Write(&count,4,0);
 if (FAILED(result)) return result;
 for(int i=0;i<count;++i) { result=stream->Write(&Vector[i],4,0);if (FAILED(result)) return result; }
 return 0;
}
