authentic_match_card(struct sc_card *card)
{
	struct sc_context *ctx = card->ctx;
	int i;

	sc_log_hex(ctx, "STR", card->atr.value, card->atr.len);
	i = _sc_match_atr(card, authentic_known_atrs, &card->type);
	if (i < 0)   {
		sc_log(ctx, "STR");
		return 0;
	}

	sc_log(ctx, "STR", authentic_known_atrs[i].name);
	return 1;
}