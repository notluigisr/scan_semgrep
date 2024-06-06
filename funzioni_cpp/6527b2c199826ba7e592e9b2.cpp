static void handle_PASS(ctrl_t *ctrl, char *pass)
{
	if (!ctrl->name[0]) {
		send_msg(ctrl->sd, "STR");
		return;
	}

	strlcpy(ctrl->pass, pass, sizeof(ctrl->pass));
	if (check_user_pass(ctrl) < 0) {
		LOG("STR", ctrl->name, ctrl->clientaddr);
		send_msg(ctrl->sd, "STR");
		return;
	}

	INFO("STR", ctrl->name, ctrl->clientaddr);
	send_msg(ctrl->sd, "STR");
}