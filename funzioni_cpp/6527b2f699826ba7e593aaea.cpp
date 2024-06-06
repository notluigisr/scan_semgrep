  LEX_STRING *make_lex_string(const char* str, uint length)
  {
    LEX_STRING *lex_str;
    if (!(lex_str= (LEX_STRING *)alloc_root(mem_root, sizeof(LEX_STRING))))
      return 0;
    return make_lex_string(lex_str, str, length);
  }