static inline void drbg_set_testdata(struct drbg_state *drbg,
				     struct drbg_test_data *test_data)
{
	if (!test_data || !test_data->testentropy)
		return;
	mutex_lock(&drbg->drbg_mutex);;
	drbg->test_data = test_data;
	mutex_unlock(&drbg->drbg_mutex);
}