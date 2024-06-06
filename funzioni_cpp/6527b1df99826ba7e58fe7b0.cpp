xmlSetBufferAllocationScheme(xmlBufferAllocationScheme scheme) {
    if ((scheme == XML_BUFFER_ALLOC_EXACT) ||
        (scheme == XML_BUFFER_ALLOC_DOUBLEIT) ||
        (scheme == XML_BUFFER_ALLOC_HYBRID))
	xmlBufferAllocScheme = scheme;
}