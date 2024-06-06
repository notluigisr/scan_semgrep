sixel_allocator_malloc(
    sixel_allocator_t    *allocator,  
    size_t               n)           
{
    
    assert(allocator);
    assert(allocator->fn_malloc);

    if (n == 0) {
        sixel_helper_set_additional_message(
            "STR");
        return NULL;
    }
    return allocator->fn_malloc(n);
}