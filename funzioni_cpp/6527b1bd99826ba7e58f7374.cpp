static void process_stat_settings(ADD_STAT add_stats, void *c) {
    assert(add_stats);
    APPEND_STAT("STR", (unsigned long long)settings.maxbytes);
    APPEND_STAT("STR", settings.maxconns);
    APPEND_STAT("STR", settings.port);
    APPEND_STAT("STR", settings.udpport);
    APPEND_STAT("STR");
    APPEND_STAT("STR", settings.verbose);
    APPEND_STAT("STR", (unsigned long)settings.oldest_live);
    APPEND_STAT("STR");
    APPEND_STAT("STR",
                settings.socketpath ? settings.socketpath : "STR");
    APPEND_STAT("STR", settings.access);
    APPEND_STAT("STR", settings.factor);
    APPEND_STAT("STR", settings.chunk_size);
    APPEND_STAT("STR", settings.num_threads);
    APPEND_STAT("STR", settings.num_threads_per_udp);
    APPEND_STAT("STR", settings.prefix_delimiter);
    APPEND_STAT("STR",
                settings.detail_enabled ? "STR");
    APPEND_STAT("STR", settings.reqs_per_event);
    APPEND_STAT("STR");
    APPEND_STAT("STR", settings.backlog);
    APPEND_STAT("STR",
                prot_text(settings.binding_protocol));
    APPEND_STAT("STR");
    APPEND_STAT("STR", settings.item_size_max);
    APPEND_STAT("STR");
    APPEND_STAT("STR", settings.hashpower_init);
    APPEND_STAT("STR");
    APPEND_STAT("STR", settings.slab_automove);
    APPEND_STAT("STR", settings.tail_repair_time);
    APPEND_STAT("STR");
}