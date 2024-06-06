xfs_alloc_lookup_eq(
	struct xfs_btree_cur	*cur,	
	xfs_agblock_t		bno,	
	xfs_extlen_t		len,	
	int			*stat)	
{
	int			error;

	cur->bc_rec.a.ar_startblock = bno;
	cur->bc_rec.a.ar_blockcount = len;
	error = xfs_btree_lookup(cur, XFS_LOOKUP_EQ, stat);
	cur->bc_private.a.priv.abt.active = (*stat == 1);
	return error;
}