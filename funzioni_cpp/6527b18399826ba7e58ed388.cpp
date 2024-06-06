static int arc_emac_tx(struct sk_buff *skb, struct net_device *ndev)
{
	struct arc_emac_priv *priv = netdev_priv(ndev);
	unsigned int len, *txbd_curr = &priv->txbd_curr;
	struct net_device_stats *stats = &ndev->stats;
	__le32 *info = &priv->txbd[*txbd_curr].info;
	dma_addr_t addr;

	if (skb_padto(skb, ETH_ZLEN))
		return NETDEV_TX_OK;

	len = max_t(unsigned int, ETH_ZLEN, skb->len);

	if (unlikely(!arc_emac_tx_avail(priv))) {
		netif_stop_queue(ndev);
		netdev_err(ndev, "STR");
		return NETDEV_TX_BUSY;
	}

	addr = dma_map_single(&ndev->dev, (void *)skb->data, len,
			      DMA_TO_DEVICE);

	if (unlikely(dma_mapping_error(&ndev->dev, addr))) {
		stats->tx_dropped++;
		stats->tx_errors++;
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}
	dma_unmap_addr_set(&priv->tx_buff[*txbd_curr], addr, addr);
	dma_unmap_len_set(&priv->tx_buff[*txbd_curr], len, len);

	priv->tx_buff[*txbd_curr].skb = skb;
	priv->txbd[*txbd_curr].data = cpu_to_le32(addr);

	
	wmb();

	skb_tx_timestamp(skb);

	*info = cpu_to_le32(FOR_EMAC | FIRST_OR_LAST_MASK | len);

	
	*txbd_curr = (*txbd_curr + 1) % TX_BD_NUM;

	
	smp_mb();

	if (!arc_emac_tx_avail(priv)) {
		netif_stop_queue(ndev);
		
		smp_mb();
		if (arc_emac_tx_avail(priv))
			netif_start_queue(ndev);
	}

	arc_reg_set(priv, R_STATUS, TXPL_MASK);

	return NETDEV_TX_OK;
}