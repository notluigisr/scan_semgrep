static int rbd_handle_request_lock(struct rbd_device *rbd_dev, u8 struct_v,
				   void **p)
{
	struct rbd_client_id my_cid = rbd_get_cid(rbd_dev);
	struct rbd_client_id cid = { 0 };
	int result = 1;

	if (struct_v >= 2) {
		cid.gid = ceph_decode_64(p);
		cid.handle = ceph_decode_64(p);
	}

	dout("STR", __func__, rbd_dev, cid.gid,
	     cid.handle);
	if (rbd_cid_equal(&cid, &my_cid))
		return result;

	down_read(&rbd_dev->lock_rwsem);
	if (__rbd_is_lock_owner(rbd_dev)) {
		if (rbd_dev->lock_state == RBD_LOCK_STATE_LOCKED &&
		    rbd_cid_equal(&rbd_dev->owner_cid, &rbd_empty_cid))
			goto out_unlock;

		
		result = 0;

		if (rbd_dev->lock_state == RBD_LOCK_STATE_LOCKED) {
			if (!rbd_dev->opts->exclusive) {
				dout("STR",
				     __func__, rbd_dev);
				queue_work(rbd_dev->task_wq,
					   &rbd_dev->unlock_work);
			} else {
				
				result = -EROFS;
			}
		}
	}

out_unlock:
	up_read(&rbd_dev->lock_rwsem);
	return result;
}