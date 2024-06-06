rsvg_cairo_new_drawing_ctx (cairo_t * cr, RsvgHandle * handle)
{
    RsvgDimensionData data;
    RsvgDrawingCtx *draw;
    RsvgCairoRender *render;
    RsvgState *state;
    cairo_matrix_t affine;
    double bbx0, bby0, bbx1, bby1;

    rsvg_handle_get_dimensions (handle, &data);
    if (data.width == 0 || data.height == 0)
        return NULL;

    draw = g_new (RsvgDrawingCtx, 1);

    cairo_get_matrix (cr, &affine);

    
    rsvg_cairo_transformed_image_bounding_box (&affine,
                                               data.width, data.height,
                                               &bbx0, &bby0, &bbx1, &bby1);

    render = rsvg_cairo_render_new (cr, bbx1 - bbx0, bby1 - bby0);

    if (!render)
        return NULL;

    draw->render = (RsvgRender *) render;
    render->offset_x = bbx0;
    render->offset_y = bby0;

    draw->state = NULL;

    draw->defs = handle->priv->defs;
    draw->base_uri = g_strdup (handle->priv->base_uri);
    draw->dpi_x = handle->priv->dpi_x;
    draw->dpi_y = handle->priv->dpi_y;
    draw->vb.rect.width = data.em;
    draw->vb.rect.height = data.ex;
    draw->pango_context = NULL;
    draw->drawsub_stack = NULL;
    draw->ptrs = NULL;

    rsvg_state_push (draw);
    state = rsvg_current_state (draw);

    
    cairo_matrix_multiply (&state->affine, &affine, &state->affine);

    
    cairo_matrix_init_scale (&affine, data.width / data.em, data.height / data.ex);
    cairo_matrix_multiply (&state->affine, &affine, &state->affine);

    
    state->affine.x0 -= render->offset_x;
    state->affine.y0 -= render->offset_y;

    rsvg_bbox_init (&((RsvgCairoRender *) draw->render)->bbox, &state->affine);

    return draw;
}