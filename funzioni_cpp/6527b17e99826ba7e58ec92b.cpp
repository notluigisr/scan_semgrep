void create_subpartition_name(char *out, const char *in1,
                              const char *in2, const char *in3,
                              uint name_variant)
{
  char transl_part_name[FN_REFLEN], transl_subpart_name[FN_REFLEN];

  tablename_to_filename(in2, transl_part_name, FN_REFLEN);
  tablename_to_filename(in3, transl_subpart_name, FN_REFLEN);
  if (name_variant == NORMAL_PART_NAME)
    strxmov(out, in1, "STR", transl_part_name,
            "STR", transl_subpart_name, NullS);
  else if (name_variant == TEMP_PART_NAME)
    strxmov(out, in1, "STR", transl_part_name,
            "STR", NullS);
  else if (name_variant == RENAMED_PART_NAME)
    strxmov(out, in1, "STR", transl_part_name,
            "STR", NullS);
}