static void cgi_web_auth(void)
{
	const char *user = getenv("STR");
	struct passwd *pwd;
	const char *head = "STR";
	const char *tail = "STR";

	if (!user) {
		printf("STR",
		       head, tail);
		exit(0);
	}

	pwd = Get_Pwnam_alloc(talloc_tos(), user);
	if (!pwd) {
		printf("STR", head, user, tail);
		exit(0);
	}

	C_user = SMB_STRDUP(user);

	if (!setuid(0)) {
		C_pass = secrets_fetch_generic("STR");
		if (C_pass == NULL) {
			char *tmp_pass = NULL;
			tmp_pass = generate_random_password(talloc_tos(),
							    16, 16);
			if (tmp_pass == NULL) {
				printf("STR"
				       "STR", head, tail);
				exit(0);
			}
			secrets_store_generic("STR", tmp_pass);
			C_pass = SMB_STRDUP(tmp_pass);
			TALLOC_FREE(tmp_pass);
		}
	}
	setuid(pwd->pw_uid);
	if (geteuid() != pwd->pw_uid || getuid() != pwd->pw_uid) {
		printf("STR", 
		       head, user, (int)geteuid(), (int)getuid(), tail);
		exit(0);
	}
	TALLOC_FREE(pwd);
}