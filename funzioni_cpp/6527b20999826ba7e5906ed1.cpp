bytes_fromhex_impl(PyTypeObject *type, PyObject *string)

{
    PyObject *newstring;
    char *buf;
    Py_ssize_t hexlen, byteslen, i, j;
    int top, bot;
    void *data;
    unsigned int kind;

    assert(PyUnicode_Check(string));
    if (PyUnicode_READY(string))
        return NULL;
    kind = PyUnicode_KIND(string);
    data = PyUnicode_DATA(string);
    hexlen = PyUnicode_GET_LENGTH(string);

    byteslen = hexlen/2; 
    newstring = PyBytes_FromStringAndSize(NULL, byteslen);
    if (!newstring)
        return NULL;
    buf = PyBytes_AS_STRING(newstring);
    for (i = j = 0; i < hexlen; i += 2) {
        
        while (PyUnicode_READ(kind, data, i) == ' ')
            i++;
        if (i >= hexlen)
            break;
        top = hex_digit_to_int(PyUnicode_READ(kind, data, i));
        bot = hex_digit_to_int(PyUnicode_READ(kind, data, i+1));
        if (top == -1 || bot == -1) {
            PyErr_Format(PyExc_ValueError,
                         "STR"
                         "STR", i);
            goto error;
        }
        buf[j++] = (top << 4) + bot;
    }
    if (j != byteslen && _PyBytes_Resize(&newstring, j) < 0)
        goto error;
    return newstring;

  error:
    Py_XDECREF(newstring);
    return NULL;
}