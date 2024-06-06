static char *next_string(char *string, unsigned long *secsize)
{
	
	while (string[0]) {
		string++;
		if ((*secsize)-- <= 1)
			return NULL;
	}

	
	while (!string[0]) {
		string++;
		if ((*secsize)-- <= 1)
			return NULL;
	}
	return string;
}