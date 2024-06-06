HeaderEntry* HeaderMapImpl::getExisting(const LowerCaseString& key) {
  
  
  
  
  auto lookup = staticLookup(key.get());
  if (lookup.has_value()) {
    return *lookup.value().entry_;
  }

  
  
  
  
  
  
  for (HeaderEntryImpl& header : headers_) {
    if (header.key() == key.get().c_str()) {
      return &header;
    }
  }

  return nullptr;
}