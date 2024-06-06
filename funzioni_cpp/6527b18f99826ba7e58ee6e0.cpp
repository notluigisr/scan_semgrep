  void Compute(OpKernelContext* context) override {
    const Tensor& tensor_in = context->input(0);

    PoolParameters params{context,
                          ksize_,
                          stride_,
                          padding_,
                          {},
                          FORMAT_NHWC,
                          tensor_in.shape()};
    if (!context->status().ok()) {
      return;
    }

    TensorShape out_shape({params.tensor_in_batch, params.out_height,
                           params.out_width, params.depth});
    Tensor* output = nullptr;
    OP_REQUIRES_OK(context, context->allocate_output(0, out_shape, &output));
    Tensor* argmax = nullptr;
    OP_REQUIRES_OK(context, context->allocate_output(1, out_shape, &argmax));

    LaunchMaxPoolingWithArgmax<Device, T, Targmax>::launch(
        context, params, tensor_in, output, argmax, propagate_nans_,
        include_batch_in_index_);
  }