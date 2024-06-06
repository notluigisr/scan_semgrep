  ptr_t GC_wince_get_mem(word bytes)
  {
    ptr_t result = 0; 
    word i;

    bytes = ROUNDUP_PAGESIZE(bytes);

    
    for (i = 0; i < GC_n_heap_bases; i++) {
        if (((word)(-(signed_word)GC_heap_lengths[i])
             & (GC_sysinfo.dwAllocationGranularity-1))
            >= bytes) {
            result = GC_heap_bases[i] + GC_heap_lengths[i];
            break;
        }
    }

    if (i == GC_n_heap_bases) {
        
        word res_bytes = (bytes + GC_sysinfo.dwAllocationGranularity-1)
                         & ~(GC_sysinfo.dwAllocationGranularity-1);
        
        
        
        
        result = (ptr_t) VirtualAlloc(NULL, res_bytes,
                                MEM_RESERVE | MEM_TOP_DOWN,
                                GC_pages_executable ? PAGE_EXECUTE_READWRITE :
                                                      PAGE_READWRITE);
        if (HBLKDISPL(result) != 0) ABORT("STR");
            
            
        if (GC_n_heap_bases >= MAX_HEAP_SECTS) ABORT("STR");
        if (result == NULL) return NULL;
        GC_heap_bases[GC_n_heap_bases] = result;
        GC_heap_lengths[GC_n_heap_bases] = 0;
        GC_n_heap_bases++;
    }

    
    result = (ptr_t) VirtualAlloc(result, bytes, MEM_COMMIT,
                              GC_pages_executable ? PAGE_EXECUTE_READWRITE :
                                                    PAGE_READWRITE);
#   undef IGNORE_PAGES_EXECUTABLE

    if (result != NULL) {
        if (HBLKDISPL(result) != 0) ABORT("STR");
        GC_heap_lengths[i] += bytes;
    }

    return(result);
  }