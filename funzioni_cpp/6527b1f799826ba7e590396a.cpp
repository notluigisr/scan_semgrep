static int macsec_add_dev(struct net_device *dev, sci_t sci, u8 icv_len)
{
	struct macsec_dev *macsec = macsec_priv(dev);
	struct macsec_secy *secy = &macsec->secy;

	macsec->stats = netdev_alloc_pcpu_stats(struct pcpu_secy_stats);
	if (!macsec->stats)
		return -ENOMEM;

	secy->tx_sc.stats = netdev_alloc_pcpu_stats(struct pcpu_tx_sc_stats);
	if (!secy->tx_sc.stats) {
		free_percpu(macsec->stats);
		return -ENOMEM;
	}

	if (sci == MACSEC_UNDEF_SCI)
		sci = dev_to_sci(dev, MACSEC_PORT_ES);

	secy->netdev = dev;
	secy->operational = true;
	secy->key_len = DEFAULT_SAK_LEN;
	secy->icv_len = icv_len;
	secy->validate_frames = MACSEC_VALIDATE_DEFAULT;
	secy->protect_frames = true;
	secy->replay_protect = false;

	secy->sci = sci;
	secy->tx_sc.active = true;
	secy->tx_sc.encoding_sa = DEFAULT_ENCODING_SA;
	secy->tx_sc.encrypt = DEFAULT_ENCRYPT;
	secy->tx_sc.send_sci = DEFAULT_SEND_SCI;
	secy->tx_sc.end_station = false;
	secy->tx_sc.scb = false;

	return 0;
}