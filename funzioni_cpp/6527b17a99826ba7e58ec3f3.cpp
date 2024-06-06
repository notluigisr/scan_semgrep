inline static bool jas_safe_size_mul(size_t x, size_t y, size_t *result)
{
	
	if (x && y > SIZE_MAX / x) {
		
		*result = 0;
		return false;
	}
	*result = x * y;
	return true;
}