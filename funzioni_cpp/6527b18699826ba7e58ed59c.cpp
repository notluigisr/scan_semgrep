static void SFDGetSpiros(FILE *sfd,SplineSet *cur) {
    int ch;
    spiro_cp cp;

    ch = nlgetc(sfd);		
    ch = nlgetc(sfd);		
    ch = nlgetc(sfd);		
    ch = nlgetc(sfd);		
    ch = nlgetc(sfd);		
    while ( fscanf(sfd,"STR", &cp.x, &cp.y, &cp.ty )==3 ) {
	if ( cur!=NULL ) {
	    if ( cur->spiro_cnt>=cur->spiro_max )
		cur->spiros = realloc(cur->spiros,(cur->spiro_max+=10)*sizeof(spiro_cp));
	    cur->spiros[cur->spiro_cnt++] = cp;
	}
    }
    if ( cur!=NULL && (cur->spiros[cur->spiro_cnt-1].ty&0x7f)!=SPIRO_END ) {
	if ( cur->spiro_cnt>=cur->spiro_max )
	    cur->spiros = realloc(cur->spiros,(cur->spiro_max+=1)*sizeof(spiro_cp));
	memset(&cur->spiros[cur->spiro_cnt],0,sizeof(spiro_cp));
	cur->spiros[cur->spiro_cnt++].ty = SPIRO_END;
    }
    ch = nlgetc(sfd);
    if ( ch=='E' ) {
	ch = nlgetc(sfd);		
	ch = nlgetc(sfd);		
	ch = nlgetc(sfd);		
	ch = nlgetc(sfd);		
	ch = nlgetc(sfd);		
	ch = nlgetc(sfd);		
	ch = nlgetc(sfd);		
    } else
	ungetc(ch,sfd);
}