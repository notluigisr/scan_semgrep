Tracing::Reason ConnectionManagerUtility::mutateTracingRequestHeader(
    RequestHeaderMap& request_headers, Runtime::Loader& runtime, ConnectionManagerConfig& config,
    const Router::Route* route) {
  Tracing::Reason final_reason = Tracing::Reason::NotTraceable;
  if (!config.tracingConfig()) {
    return final_reason;
  }

  auto rid_extension = config.requestIDExtension();
  const auto rid_to_integer = rid_extension->toInteger(request_headers);
  
  if (!rid_to_integer.has_value()) {
    return final_reason;
  }
  const uint64_t result = rid_to_integer.value() % 10000;

  const envoy::type::v3::FractionalPercent* client_sampling =
      &config.tracingConfig()->client_sampling_;
  const envoy::type::v3::FractionalPercent* random_sampling =
      &config.tracingConfig()->random_sampling_;
  const envoy::type::v3::FractionalPercent* overall_sampling =
      &config.tracingConfig()->overall_sampling_;

  if (route && route->tracingConfig()) {
    client_sampling = &route->tracingConfig()->getClientSampling();
    random_sampling = &route->tracingConfig()->getRandomSampling();
    overall_sampling = &route->tracingConfig()->getOverallSampling();
  }

  
  final_reason = rid_extension->getTraceReason(request_headers);
  if (Tracing::Reason::NotTraceable == final_reason) {
    if (request_headers.ClientTraceId() &&
        runtime.snapshot().featureEnabled("STR", *client_sampling)) {
      final_reason = Tracing::Reason::ClientForced;
      rid_extension->setTraceReason(request_headers, final_reason);
    } else if (request_headers.EnvoyForceTrace()) {
      final_reason = Tracing::Reason::ServiceForced;
      rid_extension->setTraceReason(request_headers, final_reason);
    } else if (runtime.snapshot().featureEnabled("STR", *random_sampling,
                                                 result)) {
      final_reason = Tracing::Reason::Sampling;
      rid_extension->setTraceReason(request_headers, final_reason);
    }
  }

  if (final_reason != Tracing::Reason::NotTraceable &&
      !runtime.snapshot().featureEnabled("STR", *overall_sampling, result)) {
    final_reason = Tracing::Reason::NotTraceable;
    rid_extension->setTraceReason(request_headers, final_reason);
  }

  return final_reason;
}