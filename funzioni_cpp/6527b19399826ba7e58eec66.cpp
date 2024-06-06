  void ValidateInputTensors(OpKernelContext* ctx, const Tensor& in0,
                            const Tensor& in1) override {
    OP_REQUIRES(
        ctx, in0.dims() >= 2,
        errors::InvalidArgument("STR", in0.dims()));

    OP_REQUIRES(
        ctx, in1.dims() >= 2,
        errors::InvalidArgument("STR", in1.dims()));
  }