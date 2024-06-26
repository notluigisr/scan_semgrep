void * calloc(size_t n, size_t lb)
{
    if (lb && n > SIZE_MAX / lb)
      return NULL;
#   if defined(GC_LINUX_THREADS) 
        
        
        {
          static GC_bool lib_bounds_set = FALSE;
          ptr_t caller = (ptr_t)__builtin_return_address(0);
          
          
          if (!EXPECT(lib_bounds_set, TRUE)) {
            GC_init_lib_bounds();
            lib_bounds_set = TRUE;
          }
          if (((word)caller >= (word)GC_libpthread_start
               && (word)caller < (word)GC_libpthread_end)
              || ((word)caller >= (word)GC_libld_start
                  && (word)caller < (word)GC_libld_end))
            return GC_malloc_uncollectable(n*lb);
          
          
        }
#   endif
    return((void *)REDIRECT_MALLOC(n*lb));
}