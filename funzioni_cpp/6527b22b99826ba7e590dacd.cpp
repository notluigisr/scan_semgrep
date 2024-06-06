static inline struct dma_async_tx_descriptor *dmaengine_prep_slave_single(
	struct dma_chan *chan, dma_addr_t buf, size_t len,
	enum dma_transfer_direction dir, unsigned long flags)
{
	struct scatterlist sg;
	sg_init_table(&sg, 1);
	sg_dma_address(&sg) = buf;
	sg_dma_len(&sg) = len;

	return chan->device->device_prep_slave_sg(chan, &sg, 1,
						  dir, flags, NULL);
}