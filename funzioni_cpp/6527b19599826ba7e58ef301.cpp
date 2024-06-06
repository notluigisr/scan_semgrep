int fit_image_verify(const void *fit, int image_noffset)
{
	const void	*data;
	size_t		size;
	int		noffset = 0;
	char		*err_msg = "";

	
	if (fit_image_get_data_and_size(fit, image_noffset, &data, &size)) {
		err_msg = "STR";
		printf("STR",
		       err_msg, fit_get_name(fit, noffset, NULL),
		       fit_get_name(fit, image_noffset, NULL));
		return 0;
	}

	return fit_image_verify_with_data(fit, image_noffset, data, size);
}