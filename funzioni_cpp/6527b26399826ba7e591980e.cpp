static ssize_t rbd_cluster_fsid_show(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct rbd_device *rbd_dev = dev_to_rbd_dev(dev);

	return sprintf(buf, "STR", &rbd_dev->rbd_client->client->fsid);
}