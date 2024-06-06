static int ltalk_rcv(struct sk_buff *skb, struct net_device *dev,
			struct packet_type *pt)
{
	
	if (skb->mac.raw[2] == 1) {
		struct ddpehdr *ddp;
		
		struct atalk_addr *ap = atalk_find_dev_addr(dev);

		if (!ap || skb->len < sizeof(struct ddpshdr))
			goto freeit;
		

		skb_push(skb, sizeof(*ddp) - 4);
		
		ddp = (struct ddpehdr *)skb->data;

		

	 	

		ddp->deh_dnode = skb->mac.raw[0];     
		ddp->deh_snode = skb->mac.raw[1];     

		ddp->deh_dnet  = ap->s_net;	
		ddp->deh_snet  = ap->s_net;
		ddp->deh_sum   = 0;		
		
		ddp->deh_len   = skb->len;
		ddp->deh_hops  = DDP_MAXHOPS;	
		
		*((__u16 *)ddp) = htons(*((__u16 *)ddp));
	}
	skb->h.raw = skb->data;

	return atalk_rcv(skb, dev, pt);
freeit:
	kfree_skb(skb);
	return 0;
}