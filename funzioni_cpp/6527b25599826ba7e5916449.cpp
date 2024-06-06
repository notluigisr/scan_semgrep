static inline void hci_role_switch_cfm(struct hci_conn *conn, __u8 status,
								__u8 role)
{
	struct hci_cb *cb;

	mutex_lock(&hci_cb_list_lock);
	list_for_each_entry(cb, &hci_cb_list, list) {
		if (cb->role_switch_cfm)
			cb->role_switch_cfm(conn, status, role);
	}
	mutex_unlock(&hci_cb_list_lock);
}