static void stream_set_pending_open(struct avdtp_stream *stream, GIOChannel *io)
{
	stream->open_acp = TRUE;
	stream->session->pending_open = stream;
	stream->session->pending_open_io = io;
	stream_set_timer(stream, REQ_TIMEOUT, stream_open_timeout);
}