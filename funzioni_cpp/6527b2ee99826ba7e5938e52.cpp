cairo_surface_t *CairoOutputDev::downscaleSurface(cairo_surface_t *orig_surface) {
  cairo_surface_t *dest_surface;
  unsigned char *dest_buffer;
  int dest_stride;
  unsigned char *orig_buffer;
  int orig_width, orig_height;
  int orig_stride;
  int scaledHeight;
  int scaledWidth;
  GBool res;

  if (printing)
    return NULL;

  orig_width = cairo_image_surface_get_width (orig_surface);
  orig_height = cairo_image_surface_get_height (orig_surface);
  getScaledSize (orig_width, orig_height, &scaledWidth, &scaledHeight);
  if (scaledWidth >= orig_width || scaledHeight >= orig_height)
    return NULL;

  dest_surface = cairo_surface_create_similar (orig_surface,
					       cairo_surface_get_content (orig_surface),
					       scaledWidth, scaledHeight);
  dest_buffer = cairo_image_surface_get_data (dest_surface);
  dest_stride = cairo_image_surface_get_stride (dest_surface);

  orig_buffer = cairo_image_surface_get_data (orig_surface);
  orig_stride = cairo_image_surface_get_stride (orig_surface);

  res = downscale_box_filter((uint32_t *)orig_buffer,
			     orig_stride, orig_width, orig_height,
			     scaledWidth, scaledHeight, 0, 0,
			     scaledWidth, scaledHeight,
			     (uint32_t *)dest_buffer, dest_stride);
  if (!res) {
    cairo_surface_destroy (dest_surface);
    return NULL;
  }

  return dest_surface;

}