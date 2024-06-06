static inline long div_ll_X_l_rem(long long divs, long div, long *rem)
{
	long dum2;
	asm("STR"(*rem)
	    : "STR"(divs));

	return dum2;

}