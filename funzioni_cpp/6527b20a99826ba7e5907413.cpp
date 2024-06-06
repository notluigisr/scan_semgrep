static ssize_t loop_attr_sizelimit_show(struct loop_device *lo, char *buf)
{
	return sprintf(buf, "STR", (unsigned long long)lo->lo_sizelimit);
}