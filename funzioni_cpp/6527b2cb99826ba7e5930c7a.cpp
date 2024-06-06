static long vhost_vdpa_set_status(struct vhost_vdpa *v, u8 __user *statusp)
{
	struct vdpa_device *vdpa = v->vdpa;
	const struct vdpa_config_ops *ops = vdpa->config;
	u8 status, status_old;
	int ret, nvqs = v->nvqs;
	u16 i;

	if (copy_from_user(&status, statusp, sizeof(status)))
		return -EFAULT;

	status_old = ops->get_status(vdpa);

	
	if (status != 0 && (status_old & ~status) != 0)
		return -EINVAL;

	if ((status_old & VIRTIO_CONFIG_S_DRIVER_OK) && !(status & VIRTIO_CONFIG_S_DRIVER_OK))
		for (i = 0; i < nvqs; i++)
			vhost_vdpa_unsetup_vq_irq(v, i);

	if (status == 0) {
		ret = ops->reset(vdpa);
		if (ret)
			return ret;
	} else
		ops->set_status(vdpa, status);

	if ((status & VIRTIO_CONFIG_S_DRIVER_OK) && !(status_old & VIRTIO_CONFIG_S_DRIVER_OK))
		for (i = 0; i < nvqs; i++)
			vhost_vdpa_setup_vq_irq(v, i);

	return 0;
}