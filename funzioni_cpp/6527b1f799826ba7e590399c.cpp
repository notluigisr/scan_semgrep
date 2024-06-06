static sci_t make_sci(u8 *addr, __be16 port)
{
	sci_t sci;

	memcpy(&sci, addr, ETH_ALEN);
	memcpy(((char *)&sci) + ETH_ALEN, &port, sizeof(port));

	return sci;
}