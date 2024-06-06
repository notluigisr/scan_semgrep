cib_timeout_handler(gpointer data)
{
    struct timer_rec_s *timer = data;

    timer_expired = TRUE;
    crm_err("STR", timer->call_id, timer->timeout);

    
    return TRUE;
}