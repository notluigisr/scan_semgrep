HttpHeader::getList(Http::HdrType id, String *s) const
{
    debugs(55, 9, this << "STR" << id);
    
    assert(Http::HeaderLookupTable.lookup(id).list);

    if (!CBIT_TEST(mask, id))
        return false;

    for (auto e: entries) {
        if (e && e->id == id)
            strListAdd(s, e->value.termedBuf(), ',');
    }

    
    
    if (!s->size())
        debugs(55, 3, "STR");
    else
        debugs(55, 6, this << "STR" << s);

    return true;
}