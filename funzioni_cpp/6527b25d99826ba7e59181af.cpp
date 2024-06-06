TRIO_PUBLIC_STRING int trio_xstring_match_case TRIO_ARGS2((self, other), trio_string_t* self,
                                                          TRIO_CONST char* other)
{
	assert(self);
	assert(other);

	return trio_match_case(self->content, other);
}