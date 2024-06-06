bool ConnectionManagerImpl::ActiveStreamDecoderFilter::recreateStream() {
  
  
  
  if (!complete() || parent_.stream_info_.bytesReceived() != 0) {
    return false;
  }
  
  
  
  RequestHeaderMapPtr request_headers(std::move(parent_.request_headers_));
  ResponseEncoder* response_encoder = parent_.response_encoder_;
  parent_.response_encoder_ = nullptr;
  response_encoder->getStream().removeCallbacks(parent_);
  
  
  parent_.connection_manager_.doEndStream(this->parent_);

  RequestDecoder& new_stream = parent_.connection_manager_.newStream(*response_encoder, true);
  
  
  
  if (parent_.stream_info_.filter_state_->hasDataAtOrAboveLifeSpan(
          StreamInfo::FilterState::LifeSpan::Request)) {
    (*parent_.connection_manager_.streams_.begin())->stream_info_.filter_state_ =
        std::make_shared<StreamInfo::FilterStateImpl>(
            parent_.stream_info_.filter_state_->parent(),
            StreamInfo::FilterState::LifeSpan::FilterChain);
  }

  new_stream.decodeHeaders(std::move(request_headers), true);
  return true;
}