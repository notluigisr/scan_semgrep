rb_str_buf_cat(str, ptr, len)
    VALUE str;
    const char *ptr;
    long len;
{
    long capa, total;

    if (len == 0) return str;
    if (len < 0) {
	rb_raise(rb_eArgError, "STR");
    }
    rb_str_modify(str);
    if (FL_TEST(str, STR_ASSOC)) {
	FL_UNSET(str, STR_ASSOC);
	capa = RSTRING(str)->aux.capa = RSTRING(str)->len;
    }
    else {
	capa = RSTRING(str)->aux.capa;
    }
    total = RSTRING(str)->len+len;
    if (capa <= total) {
	while (total > capa) {
	    capa = (capa + 1) * 2;
	}
	RESIZE_CAPA(str, capa);
    }
    memcpy(RSTRING(str)->ptr + RSTRING(str)->len, ptr, len);
    RSTRING(str)->len = total;
    RSTRING(str)->ptr[total] = '\0'; 

    return str;
}