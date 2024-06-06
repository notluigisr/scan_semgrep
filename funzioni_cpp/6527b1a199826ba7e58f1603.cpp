utils_clear_filled_connection_certs (NMConnection *connection)
{
	NMSetting8021x *s_8021x;

	g_return_if_fail (connection != NULL);

	s_8021x = NM_SETTING_802_1X (nm_connection_get_setting (connection, NM_TYPE_SETTING_802_1X));
	if (!s_8021x)
		return;

	g_object_set (s_8021x,
	              NM_SETTING_802_1X_CA_CERT, NULL,
	              NM_SETTING_802_1X_CLIENT_CERT, NULL,
	              NM_SETTING_802_1X_PRIVATE_KEY, NULL,
	              NM_SETTING_802_1X_PHASE2_CA_CERT, NULL,
	              NM_SETTING_802_1X_PHASE2_CLIENT_CERT, NULL,
	              NM_SETTING_802_1X_PHASE2_PRIVATE_KEY, NULL,
	              NULL);
}