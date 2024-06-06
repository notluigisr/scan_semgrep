void ClientConnectionImpl::onResetStream(StreamResetReason reason) {
  
  if (!pending_responses_.empty()) {
    pending_responses_.clear();
    request_encoder_->runResetCallbacks(reason);
  }
}