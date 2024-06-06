static void l2cap_chan_destroy(struct kref *kref)
{
	struct l2cap_chan *chan = container_of(kref, struct l2cap_chan, kref);

	BT_DBG("STR", chan);

	write_lock(&chan_list_lock);
	list_del(&chan->global_l);
	write_unlock(&chan_list_lock);

	kfree(chan);
}