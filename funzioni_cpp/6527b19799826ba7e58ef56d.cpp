static int netbk_count_requests(struct xenvif *vif,
				struct xen_netif_tx_request *first,
				struct xen_netif_tx_request *txp,
				int work_to_do)
{
	RING_IDX cons = vif->tx.req_cons;
	int frags = 0;

	if (!(first->flags & XEN_NETTXF_more_data))
		return 0;

	do {
		if (frags >= work_to_do) {
			netdev_dbg(vif->dev, "STR");
			return -frags;
		}

		if (unlikely(frags >= MAX_SKB_FRAGS)) {
			netdev_dbg(vif->dev, "STR");
			return -frags;
		}

		memcpy(txp, RING_GET_REQUEST(&vif->tx, cons + frags),
		       sizeof(*txp));
		if (txp->size > first->size) {
			netdev_dbg(vif->dev, "STR");
			return -frags;
		}

		first->size -= txp->size;
		frags++;

		if (unlikely((txp->offset + txp->size) > PAGE_SIZE)) {
			netdev_dbg(vif->dev, "STR",
				 txp->offset, txp->size);
			return -frags;
		}
	} while ((txp++)->flags & XEN_NETTXF_more_data);
	return frags;
}