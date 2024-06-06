static char *get_netscape_format(const struct Cookie *co)
{
  return aprintf(
    "STR"     
    "STR" 
    "STR"   
    "STR"   
    "STR"   
    "STR"   
    "STR"   
    "STR",    
    co->httponly?"STR",
    
    (co->tailmatch && co->domain && co->domain[0] != '.')? "STR",
    co->domain?co->domain:"STR",
    co->tailmatch?"STR",
    co->path?co->path:"STR",
    co->secure?"STR",
    co->expires,
    co->name,
    co->value?co->value:"");
}