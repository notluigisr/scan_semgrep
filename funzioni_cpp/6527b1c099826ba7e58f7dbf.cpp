GetCurrentDateTime(struct pg_tm * tm)
{
	int			tz;
	fsec_t		fsec;

	timestamp2tm(GetCurrentTransactionStartTimestamp(), &tz, tm, &fsec,
				 NULL, NULL);
	
}