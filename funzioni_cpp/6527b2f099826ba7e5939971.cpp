static void test_do_deinit(void)
{
	dict_deinit(&keys_dict);
	dict_driver_unregister(&dict_driver_file);
	oauth2_validation_key_cache_deinit(&key_cache);
	i_unlink("STR");
	buffer_free(&hs_sign_key);
	dcrypt_deinitialize();
}