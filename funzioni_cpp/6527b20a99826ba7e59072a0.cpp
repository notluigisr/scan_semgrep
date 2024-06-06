static int filter_implies_image(fz_context *ctx, pdf_obj *o)
{
	if (!o)
		return 0;
	if (pdf_is_name(ctx, o))
		return is_image_filter(pdf_to_name(ctx, o));
	if (pdf_is_array(ctx, o))
	{
		int i, len;
		len = pdf_array_len(ctx, o);
		for (i = 0; i < len; i++)
			if (is_image_filter(pdf_to_name(ctx, pdf_array_get(ctx, o, i))))
				return 1;
	}
	return 0;
}