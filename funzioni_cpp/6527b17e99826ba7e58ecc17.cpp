struct bus_id_priv *get_busid_priv(const char *busid)
{
	int idx;
	struct bus_id_priv *bid = NULL;

	spin_lock(&busid_table_lock);
	idx = get_busid_idx(busid);
	if (idx >= 0)
		bid = &(busid_table[idx]);
	spin_unlock(&busid_table_lock);

	return bid;
}