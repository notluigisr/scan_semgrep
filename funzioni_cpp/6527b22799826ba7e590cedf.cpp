PicklerMemoProxy_dealloc(PicklerMemoProxyObject *self)
{
    PyObject_GC_UnTrack(self);
    Py_XDECREF(self->pickler);
    PyObject_GC_Del((PyObject *)self);
}