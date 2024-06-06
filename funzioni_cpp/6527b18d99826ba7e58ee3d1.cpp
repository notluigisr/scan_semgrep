mountopts_check(const char *opts)
{
   char buf[64];
   const char *p;
   char *end;
   unsigned long muid;
   Eina_Bool nosuid, nodev, noexec, nuid;

   nosuid = nodev = noexec = nuid = EINA_FALSE;

   
   if (eina_strlcpy(buf, opts, sizeof(buf)) >= sizeof(buf)) return EINA_FALSE;
   for (p = buf; p && p[1]; p = strchr(p + 1, ','))
     {
        if (p[0] == ',') p++;

  if (!strncmp(p, OPT, sizeof(OPT) - 1))

        CMP("STR")
        {
           nosuid = EINA_TRUE;
           continue;
        }
        CMP("STR")
        {
           nodev = EINA_TRUE;
           continue;
        }
        CMP("STR")
        {
           noexec = EINA_TRUE;
           continue;
        }
        CMP("STR") continue;
        CMP("STR") continue;
        CMP("STR") continue;
        CMP("STR") continue;
        CMP("STR")
        {
           p += 4;
           errno = 0;
           muid = strtoul(p, &end, 10);
           if (muid == ULONG_MAX) return EINA_FALSE;
           if (errno) return EINA_FALSE;
           if (end[0] != ',') return EINA_FALSE;
           if (muid != uid) return EINA_FALSE;
           nuid = EINA_TRUE;
           continue;
        }
        return EINA_FALSE;
     }
   if ((!nosuid) || (!nodev) || (!noexec) || (!nuid)) return EINA_FALSE;
   return EINA_TRUE;
}