TRIO_PUBLIC_STRING void trio_destroy TRIO_ARGS1((string), char* string)
{
	if (string)
	{
		TRIO_FREE(string);
	}
}