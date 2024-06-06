void ath9k_fatal_work(struct work_struct *work)
{
	struct ath9k_htc_priv *priv = container_of(work, struct ath9k_htc_priv,
						   fatal_work);
	struct ath_common *common = ath9k_hw_common(priv->ah);

	ath_dbg(common, FATAL, "STR");
	ath9k_htc_reset(priv);
}