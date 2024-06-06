void bpf_prog_free_id(struct bpf_prog *prog, bool do_idr_lock)
{
	
	if (!prog->aux->id)
		return;

	if (do_idr_lock)
		spin_lock_bh(&prog_idr_lock);
	else
		__acquire(&prog_idr_lock);

	idr_remove(&prog_idr, prog->aux->id);
	prog->aux->id = 0;

	if (do_idr_lock)
		spin_unlock_bh(&prog_idr_lock);
	else
		__release(&prog_idr_lock);
}