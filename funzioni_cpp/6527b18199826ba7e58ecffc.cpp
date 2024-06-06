static inline void tcp_prequeue_init(struct tcp_sock *tp)
{
	tp->ucopy.task = NULL;
	tp->ucopy.len = 0;
	tp->ucopy.memory = 0;
	skb_queue_head_init(&tp->ucopy.prequeue);
#ifdef CONFIG_NET_DMA
	tp->ucopy.dma_chan = NULL;
	tp->ucopy.wakeup = 0;
	tp->ucopy.pinned_list = NULL;
	tp->ucopy.dma_cookie = 0;
#endif
}