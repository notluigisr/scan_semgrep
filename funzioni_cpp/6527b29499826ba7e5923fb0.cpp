static int switch_user_back_permanently(void) {
    gid_t tmp_egid = save_egid;
    uid_t tmp_euid = save_euid;
    int ret = switch_user(save_euid, save_egid);
    save_euid = tmp_euid;
    save_egid = tmp_egid;
    return ret;
}