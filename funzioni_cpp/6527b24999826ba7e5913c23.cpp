re_match(regex_t* reg, const char* str, int size, int pos,
	 struct re_registers* regs)
{
  return onig_match(reg, (UChar* )str, (UChar* )(str + size),
		    (UChar* )(str + pos), regs, ONIG_OPTION_NONE);
}