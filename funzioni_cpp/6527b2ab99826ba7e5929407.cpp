static GSList *caps_to_list(uint8_t *data, size_t size,
				struct avdtp_service_capability **codec,
				gboolean *delay_reporting)
{
	struct avdtp_service_capability *cap;
	GSList *caps;

	if (delay_reporting)
		*delay_reporting = FALSE;

	if (size < sizeof(*cap))
		return NULL;

	for (caps = NULL; size >= sizeof(*cap);) {
		struct avdtp_service_capability *cpy;

		cap = (struct avdtp_service_capability *)data;

		if (sizeof(*cap) + cap->length >= size) {
			error("STR");
			break;
		}

		if (cap->category == AVDTP_MEDIA_CODEC &&
					cap->length < sizeof(**codec)) {
			error("STR");
			break;
		}

		cpy = btd_malloc(sizeof(*cpy) + cap->length);
		memcpy(cpy, cap, sizeof(*cap) + cap->length);

		size -= sizeof(*cap) + cap->length;
		data += sizeof(*cap) + cap->length;

		caps = g_slist_append(caps, cpy);

		switch (cap->category) {
		case AVDTP_MEDIA_CODEC:
			if (codec)
				*codec = cap;
			break;
		case AVDTP_DELAY_REPORTING:
			if (delay_reporting)
				*delay_reporting = TRUE;
			break;
		}
	}

	return caps;
}