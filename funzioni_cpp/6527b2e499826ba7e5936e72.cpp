rsvg_style_handler_free (RsvgSaxHandler * self)
{
    RsvgSaxHandlerStyle *z = (RsvgSaxHandlerStyle *) self;
    RsvgHandle *ctx = z->ctx;

    if (z->is_text_css)
        rsvg_parse_cssbuffer (ctx, z->style->str, z->style->len);

    g_string_free (z->style, TRUE);
    g_free (z);
}