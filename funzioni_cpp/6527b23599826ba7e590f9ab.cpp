static u64 tcp_compute_delivery_rate(const struct tcp_sock *tp)
{
	u32 rate = READ_ONCE(tp->rate_delivered);
	u32 intv = READ_ONCE(tp->rate_interval_us);
	u64 rate64 = 0;

	if (rate && intv) {
		rate64 = (u64)rate * tp->mss_cache * USEC_PER_SEC;
		do_div(rate64, intv);
	}
	return rate64;
}