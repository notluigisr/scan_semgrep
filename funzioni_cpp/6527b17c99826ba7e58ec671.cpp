void __sock_recv_timestamp(struct msghdr *msg, struct sock *sk,
	struct sk_buff *skb)
{
	int need_software_tstamp = sock_flag(sk, SOCK_RCVTSTAMP);
	struct scm_timestamping tss;
	int empty = 1;
	struct skb_shared_hwtstamps *shhwtstamps =
		skb_hwtstamps(skb);

	
	if (need_software_tstamp && skb->tstamp == 0)
		__net_timestamp(skb);

	if (need_software_tstamp) {
		if (!sock_flag(sk, SOCK_RCVTSTAMPNS)) {
			struct timeval tv;
			skb_get_timestamp(skb, &tv);
			put_cmsg(msg, SOL_SOCKET, SCM_TIMESTAMP,
				 sizeof(tv), &tv);
		} else {
			struct timespec ts;
			skb_get_timestampns(skb, &ts);
			put_cmsg(msg, SOL_SOCKET, SCM_TIMESTAMPNS,
				 sizeof(ts), &ts);
		}
	}

	memset(&tss, 0, sizeof(tss));
	if ((sk->sk_tsflags & SOF_TIMESTAMPING_SOFTWARE) &&
	    ktime_to_timespec_cond(skb->tstamp, tss.ts + 0))
		empty = 0;
	if (shhwtstamps &&
	    (sk->sk_tsflags & SOF_TIMESTAMPING_RAW_HARDWARE) &&
	    ktime_to_timespec_cond(shhwtstamps->hwtstamp, tss.ts + 2))
		empty = 0;
	if (!empty) {
		put_cmsg(msg, SOL_SOCKET,
			 SCM_TIMESTAMPING, sizeof(tss), &tss);

		if (skb->len && (sk->sk_tsflags & SOF_TIMESTAMPING_OPT_STATS))
			put_cmsg(msg, SOL_SOCKET, SCM_TIMESTAMPING_OPT_STATS,
				 skb->len, skb->data);
	}
}