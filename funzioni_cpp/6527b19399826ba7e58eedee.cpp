static void xen_netbk_tx_submit(struct xen_netbk *netbk)
{
	struct gnttab_copy *gop = netbk->tx_copy_ops;
	struct sk_buff *skb;

	while ((skb = __skb_dequeue(&netbk->tx_queue)) != NULL) {
		struct xen_netif_tx_request *txp;
		struct xenvif *vif;
		u16 pending_idx;
		unsigned data_len;

		pending_idx = *((u16 *)skb->data);
		vif = netbk->pending_tx_info[pending_idx].vif;
		txp = &netbk->pending_tx_info[pending_idx].req;

		
		if (unlikely(xen_netbk_tx_check_gop(netbk, skb, &gop))) {
			netdev_dbg(vif->dev, "STR");
			skb_shinfo(skb)->nr_frags = 0;
			kfree_skb(skb);
			continue;
		}

		data_len = skb->len;
		memcpy(skb->data,
		       (void *)(idx_to_kaddr(netbk, pending_idx)|txp->offset),
		       data_len);
		if (data_len < txp->size) {
			
			txp->offset += data_len;
			txp->size -= data_len;
		} else {
			
			xen_netbk_idx_release(netbk, pending_idx);
		}

		if (txp->flags & XEN_NETTXF_csum_blank)
			skb->ip_summed = CHECKSUM_PARTIAL;
		else if (txp->flags & XEN_NETTXF_data_validated)
			skb->ip_summed = CHECKSUM_UNNECESSARY;

		xen_netbk_fill_frags(netbk, skb);

		
		if (skb_headlen(skb) < PKT_PROT_LEN && skb_is_nonlinear(skb)) {
			int target = min_t(int, skb->len, PKT_PROT_LEN);
			__pskb_pull_tail(skb, target - skb_headlen(skb));
		}

		skb->dev      = vif->dev;
		skb->protocol = eth_type_trans(skb, skb->dev);

		if (checksum_setup(vif, skb)) {
			netdev_dbg(vif->dev,
				   "STR");
			kfree_skb(skb);
			continue;
		}

		vif->dev->stats.rx_bytes += skb->len;
		vif->dev->stats.rx_packets++;

		xenvif_receive_skb(vif, skb);
	}
}