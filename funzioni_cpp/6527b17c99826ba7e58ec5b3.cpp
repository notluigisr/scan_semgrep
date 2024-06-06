remove_hrtimer(struct hrtimer *timer, struct hrtimer_clock_base *base, bool restart)
{
	if (hrtimer_is_queued(timer)) {
		u8 state = timer->state;
		int reprogram;

		
		debug_deactivate(timer);
		timer_stats_hrtimer_clear_start_info(timer);
		reprogram = base->cpu_base == this_cpu_ptr(&hrtimer_bases);

		if (!restart)
			state = HRTIMER_STATE_INACTIVE;

		__remove_hrtimer(timer, base, state, reprogram);
		return 1;
	}
	return 0;
}