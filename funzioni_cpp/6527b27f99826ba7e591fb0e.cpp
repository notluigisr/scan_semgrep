write_out_new_ascii_header (const char *magic_string,
			    struct cpio_file_stat *file_hdr, int out_des)
{
  char ascii_header[110];
  char *p;

  p = stpcpy (ascii_header, magic_string);
  to_ascii_or_warn (p, file_hdr->c_ino, 8, LG_16,
		    file_hdr->c_name, _("STR"));
  p += 8;
  to_ascii_or_warn (p, file_hdr->c_mode, 8, LG_16, file_hdr->c_name,
		    _("STR"));
  p += 8;
  to_ascii_or_warn (p, file_hdr->c_uid, 8, LG_16, file_hdr->c_name,
		    _("STR"));
  p += 8;
  to_ascii_or_warn (p, file_hdr->c_gid, 8, LG_16, file_hdr->c_name,
		    _("STR"));
  p += 8;
  to_ascii_or_warn (p, file_hdr->c_nlink, 8, LG_16, file_hdr->c_name,
		    _("STR"));
  p += 8;
  to_ascii_or_warn (p, file_hdr->c_mtime, 8, LG_16, file_hdr->c_name,
		    _("STR"));
  p += 8;
  if (to_ascii_or_error (p, file_hdr->c_filesize, 8, LG_16, file_hdr->c_name,
			 _("STR")))
    return 1;
  p += 8;
  if (to_ascii_or_error (p, file_hdr->c_dev_maj, 8, LG_16, file_hdr->c_name,
			 _("STR")))
    return 1;
  p += 8;
  if (to_ascii_or_error (p, file_hdr->c_dev_min, 8, LG_16, file_hdr->c_name,
			 _("STR")))
    return 1;
  p += 8;
  if (to_ascii_or_error (p, file_hdr->c_rdev_maj, 8, LG_16, file_hdr->c_name,
			 _("STR")))
    return 1;
  p += 8;
  if (to_ascii_or_error (p, file_hdr->c_rdev_min, 8, LG_16, file_hdr->c_name,
			 _("STR")))
    return 1;
  p += 8;
  if (to_ascii_or_error (p, file_hdr->c_namesize, 8, LG_16, file_hdr->c_name,
			 _("STR")))
    return 1;
  p += 8;
  to_ascii (p, file_hdr->c_chksum & 0xffffffff, 8, LG_16, false);

  tape_buffered_write (ascii_header, out_des, sizeof ascii_header);

  
  tape_buffered_write (file_hdr->c_name, out_des, (long) file_hdr->c_namesize);
  tape_pad_output (out_des, file_hdr->c_namesize + sizeof ascii_header);
  return 0;
}  