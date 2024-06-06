    if (!NIL_P(ret)) {
        
        thr_crit_bup = rb_thread_critical;
        rb_thread_critical = Qtrue;

        ret = TkStringValue(ret);
        DUMP1("STR");
        Tcl_AppendResult(interp, RSTRING_PTR(ret), (char *)NULL);

        rb_thread_critical = thr_crit_bup;
    }