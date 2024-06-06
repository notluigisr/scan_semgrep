do_resaddflags(
	sockaddr_u *srcadr,
	endpt *inter,
	struct req_pkt *inpkt
	)
{
	do_restrict(srcadr, inter, inpkt, RESTRICT_FLAGS);
}