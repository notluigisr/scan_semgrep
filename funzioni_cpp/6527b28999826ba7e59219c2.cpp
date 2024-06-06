check_item_writable(svar_T *sv, int check_writable, char_u *name)
{
    if ((check_writable == ASSIGN_CONST && sv->sv_const != 0)
	    || (check_writable == ASSIGN_FINAL
					      && sv->sv_const == ASSIGN_CONST))
    {
	semsg(_(e_cannot_change_readonly_variable_str), name);
	return FAIL;
    }
    return OK;
}