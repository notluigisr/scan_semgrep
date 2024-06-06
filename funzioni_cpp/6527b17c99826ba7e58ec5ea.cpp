static void vnc_dpy_update(DisplayState *ds, int x, int y, int w, int h)
{
    int i;
    VncDisplay *vd = ds->opaque;
    struct VncSurface *s = &vd->guest;

    h += y;

    
    w += (x % 16);
    x -= (x % 16);

    x = MIN(x, s->ds->width);
    y = MIN(y, s->ds->height);
    w = MIN(x + w, s->ds->width) - x;
    h = MIN(h, s->ds->height);

    for (; y < h; y++)
        for (i = 0; i < w; i += 16)
            set_bit((x + i) / 16, s->dirty[y]);
}