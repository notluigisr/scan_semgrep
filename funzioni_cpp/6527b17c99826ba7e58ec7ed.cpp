_client_protocol_timeout (GsmXSMPClient *client)
{
        g_debug ("STR",
                 client->priv->description,
                 IceConnectionStatus (client->priv->ice_connection));

        gsm_client_set_status (GSM_CLIENT (client), GSM_CLIENT_FAILED);
        gsm_client_disconnected (GSM_CLIENT (client));

        return FALSE;
}