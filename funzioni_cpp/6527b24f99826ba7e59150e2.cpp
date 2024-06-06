oneright(void)
{
    char_u	*ptr;
    int		l;

    if (virtual_active())
    {
	pos_T	prevpos = curwin->w_cursor;

	
	ptr = ml_get_cursor();
	coladvance(getviscol() + ((*ptr != TAB
					  && vim_isprintc((*mb_ptr2char)(ptr)))
		    ? ptr2cells(ptr) : 1));
	curwin->w_set_curswant = TRUE;
	
	return (prevpos.col != curwin->w_cursor.col
		    || prevpos.coladd != curwin->w_cursor.coladd) ? OK : FAIL;
    }

    ptr = ml_get_cursor();
    if (*ptr == NUL)
	return FAIL;	    

    if (has_mbyte)
	l = (*mb_ptr2len)(ptr);
    else
	l = 1;

    
    
    if (ptr[l] == NUL && (ve_flags & VE_ONEMORE) == 0)
	return FAIL;
    curwin->w_cursor.col += l;

    curwin->w_set_curswant = TRUE;
    return OK;
}