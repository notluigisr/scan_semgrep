nfs4_free_slot(struct nfs4_slot_table *tbl, u8 free_slotid)
{
	int slotid = free_slotid;

	BUG_ON(slotid < 0 || slotid >= NFS4_MAX_SLOT_TABLE);
	
	__clear_bit(slotid, tbl->used_slots);

	
	if (slotid == tbl->highest_used_slotid) {
		slotid = find_last_bit(tbl->used_slots, tbl->max_slots);
		if (slotid < tbl->max_slots)
			tbl->highest_used_slotid = slotid;
		else
			tbl->highest_used_slotid = -1;
	}
	dprintk("STR", __func__,
		free_slotid, tbl->highest_used_slotid);
}