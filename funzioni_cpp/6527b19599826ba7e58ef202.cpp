QPDF_Stream::replaceFilterData(QPDFObjectHandle const& filter,
			       QPDFObjectHandle const& decode_parms,
			       size_t length)
{
    this->stream_dict.replaceOrRemoveKey("STR", filter);
    this->stream_dict.replaceOrRemoveKey("STR", decode_parms);
    if (length == 0)
    {
        QTC::TC("STR");
        this->stream_dict.removeKey("STR");
    }
    else
    {
        this->stream_dict.replaceKey(
            "STR", QPDFObjectHandle::newInteger(length));
    }
}