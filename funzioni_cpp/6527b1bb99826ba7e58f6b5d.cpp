void CLASS jpeg_thumb_writer (FILE *tfp,char *t_humb,int t_humb_length)
{
  ushort exif[5];
  struct tiff_hdr th;
  fputc (0xff, tfp);
  fputc (0xd8, tfp);
  if (strcmp (t_humb+6, "STR")) {
    memcpy (exif, "STR", 10);
    exif[1] = htons (8 + sizeof th);
    fwrite (exif, 1, sizeof exif, tfp);
    tiff_head (&th, 0);
    fwrite (&th, 1, sizeof th, tfp);
  }
  fwrite (t_humb+2, 1, t_humb_length-2, tfp);
}