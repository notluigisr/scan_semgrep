void pcntl_signal_dispatch()
{
	zval *param, **handle, *retval;
	struct php_pcntl_pending_signal *queue, *next;
	sigset_t mask;
	sigset_t old_mask;
	TSRMLS_FETCH();
		
	
	sigfillset(&mask);
	sigprocmask(SIG_BLOCK, &mask, &old_mask);

	
	if (! PCNTL_G(head) || PCNTL_G(processing_signal_queue)) {
		sigprocmask(SIG_SETMASK, &old_mask, NULL);
		return;
	}

	
	PCNTL_G(processing_signal_queue) = 1;

	queue = PCNTL_G(head);
	PCNTL_G(head) = NULL; 
	
	

	while (queue) {
		if (zend_hash_index_find(&PCNTL_G(php_signal_table), queue->signo, (void **) &handle)==SUCCESS) {
			MAKE_STD_ZVAL(retval);
			MAKE_STD_ZVAL(param);
			ZVAL_NULL(retval);
			ZVAL_LONG(param, queue->signo);

			
			
			call_user_function(EG(function_table), NULL, *handle, retval, 1, &param TSRMLS_CC);
			zval_ptr_dtor(&param);
			zval_ptr_dtor(&retval);
		}

		next = queue->next;
		queue->next = PCNTL_G(spares);
		PCNTL_G(spares) = queue;
		queue = next;
	}

	
	PCNTL_G(processing_signal_queue) = 0;
	
	
	sigprocmask(SIG_SETMASK, &old_mask, NULL);
}