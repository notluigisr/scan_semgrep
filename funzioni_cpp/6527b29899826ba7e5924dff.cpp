xdiff_out(
	long start_a,
	long count_a,
	long start_b,
	long count_b,
	void *priv)
{
    diffout_T	*dout = (diffout_T *)priv;
    diffhunk_T *p = ALLOC_ONE(diffhunk_T);

    if (p == NULL)
	return -1;

    if (ga_grow(&dout->dout_ga, 1) == FAIL)
    {
	vim_free(p);
	return -1;
    }

    p->lnum_orig  = start_a + 1;
    p->count_orig = count_a;
    p->lnum_new   = start_b + 1;
    p->count_new  = count_b;
    ((diffhunk_T **)dout->dout_ga.ga_data)[dout->dout_ga.ga_len++] = p;
    return 0;
}