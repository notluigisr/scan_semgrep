static int gnutls_system_mutex_init(void **priv)
{
	pthread_mutex_t *lock = malloc(sizeof(pthread_mutex_t));
	int ret;

	if (lock == NULL)
		return GNUTLS_E_MEMORY_ERROR;

	ret = pthread_mutex_init(lock, NULL);
	if (ret) {
		free(lock);
		gnutls_assert();
		return GNUTLS_E_LOCKING_ERROR;
	}

	*priv = lock;

	return 0;
}