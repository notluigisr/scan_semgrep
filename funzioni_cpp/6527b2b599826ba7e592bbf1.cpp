void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  v8::Isolate* isolate = context->GetIsolate();
  gin_helper::Dictionary dict(isolate, exports);
  dict.Set("STR", WebContents::GetConstructor(isolate)
                              ->GetFunction(context)
                              .ToLocalChecked());
  dict.SetMethod("STR", &WebContents::Create);
  dict.SetMethod("STR", &WebContents::FromWeakMapID);
  dict.SetMethod("STR", &WebContents::GetAll);
}