port::Status CudnnSupport::DoFusedConvolve(
    Stream* stream, const dnn::BatchDescriptor& conv_input_descriptor,
    const DeviceMemory<float>& conv_input_data, float conv_input_scale,
    const dnn::FilterDescriptor& filter_descriptor,
    const DeviceMemory<float>& filter_data,
    const dnn::ConvolutionDescriptor& convolution_descriptor,
    const DeviceMemory<float>& side_input_data, float side_input_scale,
    const dnn::BatchDescriptor& bias_descriptor,
    const DeviceMemory<float>& biases, dnn::ActivationMode activation_mode,
    const dnn::BatchDescriptor& output_descriptor,
    DeviceMemory<float>* output_data, ScratchAllocator* scratch_allocator,
    const dnn::AlgorithmConfig& algorithm_config,
    dnn::ProfileResult* output_profile_result) {
  return DoFusedConvolveImpl(
      stream, conv_input_descriptor, conv_input_data, conv_input_scale,
      filter_descriptor, filter_data, convolution_descriptor, side_input_data,
      side_input_scale, bias_descriptor, biases, activation_mode,
      output_descriptor, output_data,
      GetConvAccumulatorType(dnn::DataType::kFloat), scratch_allocator,
      algorithm_config, output_profile_result);
}