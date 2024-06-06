static bool l2cap_check_enc_key_size(struct hci_conn *hcon)
{
	
	return (!test_bit(HCI_CONN_ENCRYPT, &hcon->flags) ||
		hcon->enc_key_size > HCI_MIN_ENC_KEY_SIZE);
}