fbstring IOBuf::moveToFbString() {
  
  
  bool useHeapFullStorage = false;
  SharedInfoObserverEntryBase* observerListHead = nullptr;
  
  
  if (!sharedInfo() || 
      sharedInfo()->freeFn || 
      headroom() != 0 || 
      tailroom() == 0 || 
      isShared() || 
      isChained()) { 
    
    
    coalesceAndReallocate(0, computeChainDataLength(), this, 1);
  } else {
    auto info = sharedInfo();
    if (info) {
      
      
      
      useHeapFullStorage = info->useHeapFullStorage;
      
      
      
      
      observerListHead = info->observerListHead;
      info->observerListHead = nullptr;
    }
  }

  
  *writableTail() = 0;
  fbstring str(
      reinterpret_cast<char*>(writableData()),
      length(),
      capacity(),
      AcquireMallocatedString());

  if (io_buf_free_cb && sharedInfo() && sharedInfo()->userData) {
    io_buf_free_cb(
        writableData(), reinterpret_cast<size_t>(sharedInfo()->userData));
  }

  SharedInfo::invokeAndDeleteEachObserver(
      observerListHead, [](auto& entry) { entry.afterReleaseExtBuffer(); });

  if (flags() & kFlagFreeSharedInfo) {
    delete sharedInfo();
  } else {
    if (useHeapFullStorage) {
      SharedInfo::releaseStorage(sharedInfo());
    }
  }

  
  flagsAndSharedInfo_ = 0;
  buf_ = nullptr;
  clear();
  return str;
}