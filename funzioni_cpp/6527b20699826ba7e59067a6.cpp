static void *find_audio_control_unit(struct mixer_build *state,
				     unsigned char unit)
{
	
	struct uac_feature_unit_descriptor *hdr = NULL;

	while ((hdr = snd_usb_find_desc(state->buffer, state->buflen, hdr,
					USB_DT_CS_INTERFACE)) != NULL) {
		if (hdr->bLength >= 4 &&
		    hdr->bDescriptorSubtype >= UAC_INPUT_TERMINAL &&
		    hdr->bDescriptorSubtype <= UAC2_SAMPLE_RATE_CONVERTER &&
		    hdr->bUnitID == unit)
			return hdr;
	}

	return NULL;
}