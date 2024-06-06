int usb_cypress_load_firmware(struct usb_device *udev, const struct firmware *fw, int type)
{
	struct hexline *hx;
	u8 reset;
	int ret,pos=0;

	hx = kmalloc(sizeof(*hx), GFP_KERNEL);
	if (!hx)
		return -ENOMEM;

	
	reset = 1;
	if ((ret = usb_cypress_writemem(udev,cypress[type].cpu_cs_register,&reset,1)) != 1)
		err("STR");

	while ((ret = dvb_usb_get_hexline(fw, hx, &pos)) > 0) {
		deb_fw("STR", hx->addr, hx->len, hx->chk);
		ret = usb_cypress_writemem(udev, hx->addr, hx->data, hx->len);

		if (ret != hx->len) {
			err("STR",
				ret, hx->len);
			ret = -EINVAL;
			break;
		}
	}
	if (ret < 0) {
		err("STR",pos,ret);
		kfree(hx);
		return ret;
	}

	if (ret == 0) {
		
		reset = 0;
		if (ret || usb_cypress_writemem(udev,cypress[type].cpu_cs_register,&reset,1) != 1) {
			err("STR");
			ret = -EINVAL;
		}
	} else
		ret = -EIO;

	kfree(hx);

	return ret;
}