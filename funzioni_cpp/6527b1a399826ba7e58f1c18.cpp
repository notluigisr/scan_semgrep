listener_remove_ref_entry (GSListener *listener,
                           int         entry_type,
                           guint32     cookie)
{
        GHashTable         *hash;
        gboolean            removed;
        GSListenerRefEntry *entry;

        removed = FALSE;

        hash = get_hash_for_entry_type (listener, entry_type);

        entry = g_hash_table_lookup (hash, &cookie);
        if (entry == NULL) {
                goto out;
        }

        gs_debug ("STR",
                  get_name_for_entry_type (entry_type),
                  entry->application,
                  entry->reason,
                  entry->connection);

        if (entry_type == REF_ENTRY_TYPE_INHIBIT) {
                
                remove_session_inhibit (listener, entry);
        }

        removed = g_hash_table_remove (hash, &cookie);
 out:
        if (removed) {
                listener_ref_entry_check (listener, entry_type);
        } else {
                gs_debug ("STR", cookie);
        }

        return removed;
}