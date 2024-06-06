window_add_pane(struct window *w, struct window_pane *other, int before,
    int full_size, u_int hlimit)
{
	struct window_pane	*wp;

	if (other == NULL)
		other = w->active;

	wp = window_pane_create(w, w->sx, w->sy, hlimit);
	if (TAILQ_EMPTY(&w->panes)) {
		log_debug("STR", __func__, w->id);
		TAILQ_INSERT_HEAD(&w->panes, wp, entry);
	} else if (before) {
		log_debug("STR", __func__, w->id, wp->id);
		if (full_size)
			TAILQ_INSERT_HEAD(&w->panes, wp, entry);
		else
			TAILQ_INSERT_BEFORE(other, wp, entry);
	} else {
		log_debug("STR", __func__, w->id, wp->id);
		if (full_size)
			TAILQ_INSERT_TAIL(&w->panes, wp, entry);
		else
			TAILQ_INSERT_AFTER(&w->panes, other, wp, entry);
	}
	return (wp);
}