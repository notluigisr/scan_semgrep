conntrack_flush(struct conntrack *ct, const uint16_t *zone)
{
    struct conn *conn;

    ovs_mutex_lock(&ct->ct_lock);
    CMAP_FOR_EACH (conn, cm_node, &ct->conns) {
        if (!zone || *zone == conn->key.zone) {
            conn_clean_one(ct, conn);
        }
    }
    ovs_mutex_unlock(&ct->ct_lock);

    return 0;
}