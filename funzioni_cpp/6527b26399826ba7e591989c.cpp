static int _rbd_dev_v2_snap_size(struct rbd_device *rbd_dev, u64 snap_id,
				u8 *order, u64 *snap_size)
{
	__le64 snapid = cpu_to_le64(snap_id);
	int ret;
	struct {
		u8 order;
		__le64 size;
	} __attribute__ ((packed)) size_buf = { 0 };

	ret = rbd_obj_method_sync(rbd_dev, &rbd_dev->header_oid,
				  &rbd_dev->header_oloc, "STR",
				  &snapid, sizeof(snapid),
				  &size_buf, sizeof(size_buf));
	dout("STR", __func__, ret);
	if (ret < 0)
		return ret;
	if (ret < sizeof (size_buf))
		return -ERANGE;

	if (order) {
		*order = size_buf.order;
		dout("STR", (unsigned int)*order);
	}
	*snap_size = le64_to_cpu(size_buf.size);

	dout("STR",
		(unsigned long long)snap_id,
		(unsigned long long)*snap_size);

	return 0;
}