struct torture_suite *torture_smb2_notify_init(TALLOC_CTX *ctx)
{
	struct torture_suite *suite = torture_suite_create(ctx, "STR");

	torture_suite_add_1smb2_test(suite, "STR", test_valid_request);
	torture_suite_add_1smb2_test(suite, "STR", torture_smb2_notify_tcon);
	torture_suite_add_2smb2_test(suite, "STR", torture_smb2_notify_dir);
	torture_suite_add_2smb2_test(suite, "STR", torture_smb2_notify_mask);
	torture_suite_add_1smb2_test(suite, "STR", torture_smb2_notify_tree_disconnect);
	torture_suite_add_1smb2_test(suite, "STR", torture_smb2_notify_tree_disconnect_1);
	torture_suite_add_2smb2_test(suite, "STR", torture_smb2_notify_mask_change);
	torture_suite_add_1smb2_test(suite, "STR", torture_smb2_notify_close);
	torture_suite_add_1smb2_test(suite, "STR", torture_smb2_notify_ulogoff);
	torture_suite_add_1smb2_test(suite, "STR", torture_smb2_notify_session_reconnect);
	torture_suite_add_2smb2_test(suite, "STR", torture_smb2_notify_invalid_reauth);
	torture_suite_add_1smb2_test(suite, "STR", torture_smb2_notify_tree);
	torture_suite_add_2smb2_test(suite, "STR", torture_smb2_notify_basedir);
	torture_suite_add_2smb2_test(suite, "STR", torture_smb2_notify_double);
	torture_suite_add_1smb2_test(suite, "STR", torture_smb2_notify_file);
	torture_suite_add_1smb2_test(suite, "STR", torture_smb2_notify_tcp_disconnect);
	torture_suite_add_2smb2_test(suite, "STR", torture_smb2_notify_recursive);
	torture_suite_add_1smb2_test(suite, "STR", torture_smb2_notify_overflow);
	torture_suite_add_1smb2_test(suite, "STR",
				     torture_smb2_notify_rmdir1);
	torture_suite_add_1smb2_test(suite, "STR",
				     torture_smb2_notify_rmdir2);
	torture_suite_add_2smb2_test(suite, "STR",
				     torture_smb2_notify_rmdir3);
	torture_suite_add_2smb2_test(suite, "STR",
				     torture_smb2_notify_rmdir4);

	suite->description = talloc_strdup(suite, "STR");

	return suite;
}