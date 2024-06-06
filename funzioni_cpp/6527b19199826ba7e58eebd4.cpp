static __u8 *kye_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	switch (hdev->product) {
	case USB_DEVICE_ID_KYE_ERGO_525V:
		
		if (*rsize >= 74 &&
			rdesc[61] == 0x05 && rdesc[62] == 0x08 &&
			rdesc[63] == 0x19 && rdesc[64] == 0x08 &&
			rdesc[65] == 0x29 && rdesc[66] == 0x0f &&
			rdesc[71] == 0x75 && rdesc[72] == 0x08 &&
			rdesc[73] == 0x95 && rdesc[74] == 0x01) {
			hid_info(hdev,
				 "STR"
				 "STR");
			rdesc[62] = 0x09;
			rdesc[64] = 0x04;
			rdesc[66] = 0x07;
			rdesc[72] = 0x01;
			rdesc[74] = 0x08;
		}
		break;
	case USB_DEVICE_ID_KYE_EASYPEN_I405X:
		if (*rsize == EASYPEN_I405X_RDESC_ORIG_SIZE) {
			rdesc = easypen_i405x_rdesc_fixed;
			*rsize = sizeof(easypen_i405x_rdesc_fixed);
		}
		break;
	case USB_DEVICE_ID_KYE_MOUSEPEN_I608X:
		if (*rsize == MOUSEPEN_I608X_RDESC_ORIG_SIZE) {
			rdesc = mousepen_i608x_rdesc_fixed;
			*rsize = sizeof(mousepen_i608x_rdesc_fixed);
		}
		break;
	case USB_DEVICE_ID_KYE_EASYPEN_M610X:
		if (*rsize == EASYPEN_M610X_RDESC_ORIG_SIZE) {
			rdesc = easypen_m610x_rdesc_fixed;
			*rsize = sizeof(easypen_m610x_rdesc_fixed);
		}
		break;
	case USB_DEVICE_ID_GENIUS_GILA_GAMING_MOUSE:
		rdesc = kye_consumer_control_fixup(hdev, rdesc, rsize, 104,
					"STR");
		break;
	case USB_DEVICE_ID_GENIUS_GX_IMPERATOR:
		rdesc = kye_consumer_control_fixup(hdev, rdesc, rsize, 83,
					"STR");
		break;
	case USB_DEVICE_ID_GENIUS_MANTICORE:
		rdesc = kye_consumer_control_fixup(hdev, rdesc, rsize, 104,
					"STR");
		break;
	}
	return rdesc;
}