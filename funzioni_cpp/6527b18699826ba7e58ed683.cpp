static void vnc_tight_start(VncState *vs)
{
    buffer_reset(&vs->tight.tight);

    
    vs->tight.tmp = vs->output;
    vs->output = vs->tight.tight;
}