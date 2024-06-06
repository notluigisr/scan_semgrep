psutil_per_cpu_times(PyObject *self, PyObject *args) {
    double idle, kernel, systemt, user, interrupt, dpc;
    NTSTATUS status;
    _SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION *sppi = NULL;
    UINT i;
    unsigned int ncpus;
    PyObject *py_tuple = NULL;
    PyObject *py_retlist = PyList_New(0);

    if (py_retlist == NULL)
        return NULL;

    
    ncpus = psutil_get_num_cpus(1);
    if (ncpus == 0)
        goto error;

    
    
    sppi = (_SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION *) \
        malloc(ncpus * sizeof(_SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION));
    if (sppi == NULL) {
        PyErr_NoMemory();
        goto error;
    }

    
    status = psutil_NtQuerySystemInformation(
        SystemProcessorPerformanceInformation,
        sppi,
        ncpus * sizeof(_SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION),
        NULL);
    if (! NT_SUCCESS(status)) {
        psutil_SetFromNTStatusErr(
            status,
            "STR"
        );
        goto error;
    }

    
    
    idle = user = kernel = interrupt = dpc = 0;
    for (i = 0; i < ncpus; i++) {
        py_tuple = NULL;
        user = (double)((HI_T * sppi[i].UserTime.HighPart) +
                       (LO_T * sppi[i].UserTime.LowPart));
        idle = (double)((HI_T * sppi[i].IdleTime.HighPart) +
                       (LO_T * sppi[i].IdleTime.LowPart));
        kernel = (double)((HI_T * sppi[i].KernelTime.HighPart) +
                         (LO_T * sppi[i].KernelTime.LowPart));
        interrupt = (double)((HI_T * sppi[i].InterruptTime.HighPart) +
                            (LO_T * sppi[i].InterruptTime.LowPart));
        dpc = (double)((HI_T * sppi[i].DpcTime.HighPart) +
                      (LO_T * sppi[i].DpcTime.LowPart));

        
        
        
        systemt = kernel - idle;
        py_tuple = Py_BuildValue(
            "STR",
            user,
            systemt,
            idle,
            interrupt,
            dpc
        );
        if (!py_tuple)
            goto error;
        if (PyList_Append(py_retlist, py_tuple))
            goto error;
        Py_DECREF(py_tuple);
    }

    free(sppi);
    return py_retlist;

error:
    Py_XDECREF(py_tuple);
    Py_DECREF(py_retlist);
    if (sppi)
        free(sppi);
    return NULL;
}