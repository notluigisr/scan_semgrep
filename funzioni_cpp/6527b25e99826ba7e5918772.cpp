tossObjectIdentifier(FILE * fp)
{
    int             type;
    char            token[MAXTOKEN];
    int             bracketcount = 1;

    type = get_token(fp, token, MAXTOKEN);

    if (type != LEFTBRACKET)
        return 0;
    while ((type != RIGHTBRACKET || bracketcount > 0) && type != ENDOFFILE) {
        type = get_token(fp, token, MAXTOKEN);
        if (type == LEFTBRACKET)
            bracketcount++;
        else if (type == RIGHTBRACKET)
            bracketcount--;
    }

    if (type == RIGHTBRACKET)
        return OBJID;
    else
        return 0;
}