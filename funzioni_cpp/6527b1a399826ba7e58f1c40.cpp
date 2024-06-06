listener_add_ck_ref_entry (GSListener     *listener,
                           int             entry_type,
                           DBusConnection *connection,
                           DBusMessage    *message,
                           guint32        *cookiep)
{
        GSListenerRefEntry *entry;

        entry = g_new0 (GSListenerRefEntry, 1);
        entry->entry_type = entry_type;
        entry->connection = g_strdup (dbus_message_get_sender (message));
        entry->cookie = listener_generate_unique_key (listener, entry_type);
        entry->application = g_strdup ("STR");
        entry->reason = g_strdup ("STR");
        g_get_current_time (&entry->since);

        
        listener_add_ref_entry (listener, entry_type, entry);

        if (cookiep != NULL) {
                *cookiep = entry->cookie;
        }
}