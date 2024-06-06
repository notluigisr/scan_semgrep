static int ZEND_FASTCALL  ZEND_SR_SPEC_CV_TMP_HANDLER(ZEND_OPCODE_HANDLER_ARGS)
{
	zend_op *opline = EX(opline);
	zend_free_op free_op2;

	shift_right_function(&EX_T(opline->result.u.var).tmp_var,
		_get_zval_ptr_cv(&opline->op1, EX(Ts), BP_VAR_R TSRMLS_CC),
		_get_zval_ptr_tmp(&opline->op2, EX(Ts), &free_op2 TSRMLS_CC) TSRMLS_CC);

	zval_dtor(free_op2.var);
	ZEND_VM_NEXT_OPCODE();
}