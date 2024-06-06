HeaderMap::Lookup HeaderMapImpl::lookup(const LowerCaseString& key,
                                        const HeaderEntry** entry) const {
  EntryCb cb = ConstSingleton<StaticLookupTable>::get().find(key.get());
  if (cb) {
    
    
    
    
    
    
    StaticLookupResponse ref_lookup_response = cb(const_cast<HeaderMapImpl&>(*this));
    *entry = *ref_lookup_response.entry_;
    if (*entry) {
      return Lookup::Found;
    } else {
      return Lookup::NotFound;
    }
  } else {
    *entry = nullptr;
    return Lookup::NotSupported;
  }
}