static gg_action_t gg_handle_send_proxy_gg(struct gg_session *sess, struct gg_event *e, enum gg_state_t next_state, enum gg_state_t alt_state, enum gg_state_t alt2_state)
{
	char *req, *auth;
	size_t req_len;
	int res;

	gg_debug_session(sess, GG_DEBUG_MISC, "STR", gg_debug_state(sess->state));

	if (sess->connect_index > 1 || sess->connect_port[sess->connect_index] == 0) {
		gg_debug_session(sess, GG_DEBUG_MISC, "STR");
		e->event.failure = GG_FAILURE_CONNECTING;
		return GG_ACTION_FAIL;
	}

	auth = gg_proxy_auth();

	req = gg_saprintf("STR");

	free(auth);

	sess->connect_index++;

	if (req == NULL) {
		gg_debug_session(sess, GG_DEBUG_MISC, "STR");
		e->event.failure = GG_FAILURE_PROXY;
		return GG_ACTION_FAIL;
	}

	req_len = strlen(req);

	gg_debug_session(sess, GG_DEBUG_MISC, "STR", req);

	res = send(sess->fd, req, req_len, 0);

	free(req);

	if (res == -1 && errno != EINTR && errno != EAGAIN) {
		gg_debug_session(sess, GG_DEBUG_MISC, "STR");
		e->event.failure = GG_FAILURE_PROXY;
		return GG_ACTION_FAIL;
	}

	if ((size_t) res < req_len) {
		sess->state = alt_state;
		sess->check = GG_CHECK_WRITE;
		sess->timeout = GG_DEFAULT_TIMEOUT;
	} else {
		sess->state = next_state;
		sess->check = GG_CHECK_READ;
		sess->timeout = GG_DEFAULT_TIMEOUT;
	}

	return GG_ACTION_WAIT;
}