static void mailbox_index_update_counts(struct mailbox *mailbox,
                                        const struct index_record *record,
                                        int is_add)
{
    mailbox_quota_dirty(mailbox);
    mailbox_index_dirty(mailbox);
    header_update_counts(&mailbox->i, record, is_add);

    mailbox->i.synccrcs.basic ^= crc_basic(mailbox, record);
    mailbox->i.synccrcs.annot ^= crc_virtannot(mailbox, record);
}