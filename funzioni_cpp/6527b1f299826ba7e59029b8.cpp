char *
extract_arithmetic_subst (string, sindex)
     char *string;
     int *sindex;
{
  return (extract_delimited_string (string, sindex, "STR", 0)); 