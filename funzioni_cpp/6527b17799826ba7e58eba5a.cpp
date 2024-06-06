evbuffer_chain_new(size_t size)
{
	struct evbuffer_chain *chain;
	size_t to_alloc;

	size += EVBUFFER_CHAIN_SIZE;

	
	to_alloc = MIN_BUFFER_SIZE;
	while (to_alloc < size)
		to_alloc <<= 1;

	
	if ((chain = mm_malloc(to_alloc)) == NULL)
		return (NULL);

	memset(chain, 0, EVBUFFER_CHAIN_SIZE);

	chain->buffer_len = to_alloc - EVBUFFER_CHAIN_SIZE;

	
	chain->buffer = EVBUFFER_CHAIN_EXTRA(u_char, chain);

	chain->refcnt = 1;

	return (chain);
}