updateDevice(const struct header * headers, time_t t)
{
	struct device ** pp = &devlist;
	struct device * p = *pp;	
	while(p)
	{
		if(  p->headers[HEADER_NT].l == headers[HEADER_NT].l
		  && (0==memcmp(p->headers[HEADER_NT].p, headers[HEADER_NT].p, headers[HEADER_NT].l))
		  && p->headers[HEADER_USN].l == headers[HEADER_USN].l
		  && (0==memcmp(p->headers[HEADER_USN].p, headers[HEADER_USN].p, headers[HEADER_USN].l)) )
		{
			
			syslog(LOG_DEBUG, "STR", headers[HEADER_USN].l, headers[HEADER_USN].p);
			p->t = t;
			
			if(headers[HEADER_LOCATION].l > p->headers[HEADER_LOCATION].l)
			{
				struct device * tmp;
				tmp = realloc(p, sizeof(struct device)
				    + headers[0].l+headers[1].l+headers[2].l);
				if(!tmp)	
				{
					syslog(LOG_ERR, "STR");
					free(p);
					return 0;
				}
				p = tmp;
				*pp = p;
			}
			memcpy(p->data + p->headers[0].l + p->headers[1].l,
			       headers[2].p, headers[2].l);
			
			return 0;
		}
		pp = &p->next;
		p = *pp;	
	}
	syslog(LOG_INFO, "STR",
	       headers[HEADER_USN].l, headers[HEADER_USN].p);
	
	{
		char * pc;
		int i;
		p = malloc(  sizeof(struct device)
		           + headers[0].l+headers[1].l+headers[2].l );
		if(!p) {
			syslog(LOG_ERR, "STR");
			return -1;
		}
		p->next = devlist;
		p->t = t;
		pc = p->data;
		for(i = 0; i < 3; i++)
		{
			p->headers[i].p = pc;
			p->headers[i].l = headers[i].l;
			memcpy(pc, headers[i].p, headers[i].l);
			pc += headers[i].l;
		}
		devlist = p;
		sendNotifications(NOTIF_NEW, p, NULL);
	}
	return 1;
}