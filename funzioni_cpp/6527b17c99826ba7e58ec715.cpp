static void cp2112_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct cp2112_device *dev = gpiochip_get_data(chip);
	struct hid_device *hdev = dev->hdev;
	u8 *buf = dev->in_out_buffer;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&dev->lock, flags);

	buf[0] = CP2112_GPIO_SET;
	buf[1] = value ? 0xff : 0;
	buf[2] = 1 << offset;

	ret = hid_hw_raw_request(hdev, CP2112_GPIO_SET, buf,
				 CP2112_GPIO_SET_LENGTH, HID_FEATURE_REPORT,
				 HID_REQ_SET_REPORT);
	if (ret < 0)
		hid_err(hdev, "STR", ret);

	spin_unlock_irqrestore(&dev->lock, flags);
}