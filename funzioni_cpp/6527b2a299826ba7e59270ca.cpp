  void WillReleaseScriptContext(v8::Local<v8::Context> context,
                                int32_t world_id) override {
    if (weak_context_.IsEmpty() ||
        weak_context_.Get(context->GetIsolate()) == context)
      electron_ipc_remote_.reset();
  }