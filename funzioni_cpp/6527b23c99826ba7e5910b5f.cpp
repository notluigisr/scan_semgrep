httpRead(http_t *http,			
         char   *buffer,		
	 int    length)			
{
  return ((int)httpRead2(http, buffer, (size_t)length));
}