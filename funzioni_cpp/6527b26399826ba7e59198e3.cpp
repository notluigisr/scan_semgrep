compile_length_string_crude_node(StrNode* sn, regex_t* reg)
{
  if (sn->end <= sn->s)
    return 0;

  return add_compile_string_length(sn->s, 1 , (int )(sn->end - sn->s),
                                   reg);
}