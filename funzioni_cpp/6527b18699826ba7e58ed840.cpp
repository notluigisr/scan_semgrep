  void allocHeaders() override {
    ASSERT(nullptr == absl::get<RequestHeaderMapPtr>(headers_or_trailers_));
    headers_or_trailers_.emplace<RequestHeaderMapPtr>(RequestHeaderMapImpl::create());
  }