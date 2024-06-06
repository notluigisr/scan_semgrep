static inline void csrhci_fifo_wake(struct csrhci_s *s)
{
    if (!s->enable || !s->out_len)
        return;

    
    if (s->chr.chr_can_read && s->chr.chr_can_read(s->chr.handler_opaque) &&
                    s->chr.chr_read) {
        s->chr.chr_read(s->chr.handler_opaque,
                        s->outfifo + s->out_start ++, 1);
        s->out_len --;
        if (s->out_start >= s->out_size) {
            s->out_start = 0;
            s->out_size = FIFO_LEN;
        }
    }

    if (s->out_len)
        timer_mod(s->out_tm, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + s->baud_delay);
}