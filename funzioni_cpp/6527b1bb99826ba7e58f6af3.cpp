void CLASS unpacked_load_raw()
{
  int row, col, bits=0;

  while (1 << ++bits < maximum);
  read_shorts (raw_image, raw_width*raw_height);
  for (row=0; row < raw_height; row++)
    for (col=0; col < raw_width; col++)
      if ((RAW(row,col) >>= load_flags) >> bits
	&& (unsigned) (row-top_margin) < height
	&& (unsigned) (col-left_margin) < width) derror();
}