eval_expr_typval(typval_T *expr, typval_T *argv, int argc, typval_T *rettv)
{
    char_u	*s;
    char_u	buf[NUMBUFLEN];
    funcexe_T	funcexe;

    if (expr->v_type == VAR_FUNC)
    {
	s = expr->vval.v_string;
	if (s == NULL || *s == NUL)
	    return FAIL;
	CLEAR_FIELD(funcexe);
	funcexe.fe_evaluate = TRUE;
	if (call_func(s, -1, rettv, argc, argv, &funcexe) == FAIL)
	    return FAIL;
    }
    else if (expr->v_type == VAR_PARTIAL)
    {
	partial_T   *partial = expr->vval.v_partial;

	if (partial == NULL)
	    return FAIL;

	if (partial->pt_func != NULL
			  && partial->pt_func->uf_def_status != UF_NOT_COMPILED)
	{
	    funccall_T	*fc = create_funccal(partial->pt_func, rettv);
	    int		r;

	    if (fc == NULL)
		return FAIL;

	    
	    r = call_def_function(partial->pt_func, argc, argv,
					  DEF_USE_PT_ARGV, partial, fc, rettv);
	    remove_funccal();
	    if (r == FAIL)
		return FAIL;
	}
	else
	{
	    s = partial_name(partial);
	    if (s == NULL || *s == NUL)
		return FAIL;
	    CLEAR_FIELD(funcexe);
	    funcexe.fe_evaluate = TRUE;
	    funcexe.fe_partial = partial;
	    if (call_func(s, -1, rettv, argc, argv, &funcexe) == FAIL)
		return FAIL;
	}
    }
    else if (expr->v_type == VAR_INSTR)
    {
	return exe_typval_instr(expr, rettv);
    }
    else
    {
	s = tv_get_string_buf_chk_strict(expr, buf, in_vim9script());
	if (s == NULL)
	    return FAIL;
	s = skipwhite(s);
	if (eval1_emsg(&s, rettv, NULL) == FAIL)
	    return FAIL;
	if (*skipwhite(s) != NUL)  
	{
	    clear_tv(rettv);
	    semsg(_(e_invalid_expression_str), s);
	    return FAIL;
	}
    }
    return OK;
}