NIAddAffix(IspellDict *Conf, int flag, char flagflags, const char *mask, const char *find, const char *repl, int type)
{
	AFFIX	   *Affix;

	if (Conf->naffixes >= Conf->maffixes)
	{
		if (Conf->maffixes)
		{
			Conf->maffixes *= 2;
			Conf->Affix = (AFFIX *) repalloc((void *) Conf->Affix, Conf->maffixes * sizeof(AFFIX));
		}
		else
		{
			Conf->maffixes = 16;
			Conf->Affix = (AFFIX *) palloc(Conf->maffixes * sizeof(AFFIX));
		}
	}

	Affix = Conf->Affix + Conf->naffixes;

	if (strcmp(mask, "STR") == 0)
	{
		Affix->issimple = 1;
		Affix->isregis = 0;
	}
	else if (RS_isRegis(mask))
	{
		Affix->issimple = 0;
		Affix->isregis = 1;
		RS_compile(&(Affix->reg.regis), (type == FF_SUFFIX) ? true : false,
				   (mask && *mask) ? mask : VoidString);
	}
	else
	{
		int			masklen;
		int			wmasklen;
		int			err;
		pg_wchar   *wmask;
		char	   *tmask;

		Affix->issimple = 0;
		Affix->isregis = 0;
		tmask = (char *) tmpalloc(strlen(mask) + 3);
		if (type == FF_SUFFIX)
			sprintf(tmask, "STR", mask);
		else
			sprintf(tmask, "STR", mask);

		masklen = strlen(tmask);
		wmask = (pg_wchar *) tmpalloc((masklen + 1) * sizeof(pg_wchar));
		wmasklen = pg_mb2wchar_with_len(tmask, wmask, masklen);

		err = pg_regcomp(&(Affix->reg.regex), wmask, wmasklen,
						 REG_ADVANCED | REG_NOSUB,
						 DEFAULT_COLLATION_OID);
		if (err)
		{
			char		errstr[100];

			pg_regerror(err, &(Affix->reg.regex), errstr, sizeof(errstr));
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_REGULAR_EXPRESSION),
					 errmsg("STR", errstr)));
		}
	}

	Affix->flagflags = flagflags;
	if ((Affix->flagflags & FF_COMPOUNDONLY) || (Affix->flagflags & FF_COMPOUNDPERMITFLAG))
	{
		if ((Affix->flagflags & FF_COMPOUNDFLAG) == 0)
			Affix->flagflags |= FF_COMPOUNDFLAG;
	}
	Affix->flag = flag;
	Affix->type = type;

	Affix->find = (find && *find) ? cpstrdup(Conf, find) : VoidString;
	if ((Affix->replen = strlen(repl)) > 0)
		Affix->repl = cpstrdup(Conf, repl);
	else
		Affix->repl = VoidString;
	Conf->naffixes++;
}