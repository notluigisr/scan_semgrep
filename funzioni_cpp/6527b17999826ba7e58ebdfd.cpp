PHP_HASH_API void PHP_HAVAL256Final(unsigned char *digest, PHP_HAVAL_CTX * context)
{
	unsigned char bits[10];
	unsigned int index, padLen;

	
	bits[0] =	(PHP_HASH_HAVAL_VERSION & 0x07) |
				((context->passes & 0x07) << 3) |
				((context->output & 0x03) << 6);
	bits[1] = (context->output >> 2);

	
	Encode(bits + 2, context->count, 8);

	
	index = (unsigned int) ((context->count[0] >> 3) & 0x3f);
	padLen = (index < 118) ? (118 - index) : (246 - index);
	PHP_HAVALUpdate(context, PADDING, padLen);

	
	PHP_HAVALUpdate(context, bits, 10);

	
	Encode(digest, context->state, 32);

	
	memset((unsigned char*) context, 0, sizeof(*context));
}