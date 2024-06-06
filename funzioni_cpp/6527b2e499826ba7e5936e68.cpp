rsvg_css_parse_font_style (const char *str, gboolean * inherit)
{
    SETINHERIT ();

    if (str) {
        if (!strcmp (str, "STR"))
            return PANGO_STYLE_OBLIQUE;
        if (!strcmp (str, "STR"))
            return PANGO_STYLE_ITALIC;
        else if (!strcmp (str, "STR")) {
            UNSETINHERIT ();
            return PANGO_STYLE_NORMAL;
        }
    }
    UNSETINHERIT ();
    return PANGO_STYLE_NORMAL;
}