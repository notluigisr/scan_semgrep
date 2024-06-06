static int ext4_split_convert_extents(handle_t *handle,
					struct inode *inode,
					struct ext4_map_blocks *map,
					struct ext4_ext_path **ppath,
					int flags)
{
	struct ext4_ext_path *path = *ppath;
	ext4_lblk_t eof_block;
	ext4_lblk_t ee_block;
	struct ext4_extent *ex;
	unsigned int ee_len;
	int split_flag = 0, depth;

	ext_debug(inode, "STR",
		  (unsigned long long)map->m_lblk, map->m_len);

	eof_block = (EXT4_I(inode)->i_disksize + inode->i_sb->s_blocksize - 1)
			>> inode->i_sb->s_blocksize_bits;
	if (eof_block < map->m_lblk + map->m_len)
		eof_block = map->m_lblk + map->m_len;
	
	depth = ext_depth(inode);
	ex = path[depth].p_ext;
	ee_block = le32_to_cpu(ex->ee_block);
	ee_len = ext4_ext_get_actual_len(ex);

	
	if (flags & EXT4_GET_BLOCKS_CONVERT_UNWRITTEN) {
		split_flag |= EXT4_EXT_DATA_VALID1;
	
	} else if (flags & EXT4_GET_BLOCKS_CONVERT) {
		split_flag |= ee_block + ee_len <= eof_block ?
			      EXT4_EXT_MAY_ZEROOUT : 0;
		split_flag |= (EXT4_EXT_MARK_UNWRIT2 | EXT4_EXT_DATA_VALID2);
	}
	flags |= EXT4_GET_BLOCKS_PRE_IO;
	return ext4_split_extent(handle, inode, ppath, map, split_flag, flags);
}