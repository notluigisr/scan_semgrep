void __sock_recv_timestamp(struct msghdr *msg, struct sock *sk,
	struct sk_buff *skb)
{
	int need_software_tstamp = sock_flag(sk, SOCK_RCVTSTAMP);
	struct timespec ts[3];
	int empty = 1;
	struct skb_shared_hwtstamps *shhwtstamps =
		skb_hwtstamps(skb);

	
	if (need_software_tstamp && skb->tstamp.tv64 == 0)
		__net_timestamp(skb);

	if (need_software_tstamp) {
		if (!sock_flag(sk, SOCK_RCVTSTAMPNS)) {
			struct timeval tv;
			skb_get_timestamp(skb, &tv);
			put_cmsg(msg, SOL_SOCKET, SCM_TIMESTAMP,
				 sizeof(tv), &tv);
		} else {
			skb_get_timestampns(skb, &ts[0]);
			put_cmsg(msg, SOL_SOCKET, SCM_TIMESTAMPNS,
				 sizeof(ts[0]), &ts[0]);
		}
	}


	memset(ts, 0, sizeof(ts));
	if (skb->tstamp.tv64 &&
	    sock_flag(sk, SOCK_TIMESTAMPING_SOFTWARE)) {
		skb_get_timestampns(skb, ts + 0);
		empty = 0;
	}
	if (shhwtstamps) {
		if (sock_flag(sk, SOCK_TIMESTAMPING_SYS_HARDWARE) &&
		    ktime2ts(shhwtstamps->syststamp, ts + 1))
			empty = 0;
		if (sock_flag(sk, SOCK_TIMESTAMPING_RAW_HARDWARE) &&
		    ktime2ts(shhwtstamps->hwtstamp, ts + 2))
			empty = 0;
	}
	if (!empty)
		put_cmsg(msg, SOL_SOCKET,
			 SCM_TIMESTAMPING, sizeof(ts), &ts);
}