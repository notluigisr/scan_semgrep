gdm_user_get_display_name (GdmUser *user)
{
        g_return_val_if_fail (GDM_IS_USER (user), NULL);

        return (user->display_name ? user->display_name
                : gdm_user_get_real_name (user));
}