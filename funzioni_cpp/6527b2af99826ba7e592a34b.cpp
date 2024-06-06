auth_pin_is_verified(struct sc_card *card, int pin_reference, int *tries_left)
{
	struct sc_apdu apdu;
	int rv;

	sc_format_apdu(card, &apdu, SC_APDU_CASE_1, 0x20, 0, pin_reference);

	rv = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(card->ctx, rv, "STR");

	if (tries_left && apdu.sw1 == 0x63 && (apdu.sw2 & 0xF0) == 0xC0)
		*tries_left = apdu.sw2 & 0x0F;

	
	if (apdu.sw1 == 0x63 && apdu.sw2 == 0xC0)    {
		apdu.sw1 = 0x69;
		apdu.sw2 = 0x83;
	}

	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);

	return rv;
}