static void FVMenuMMInfo(GWindow gw, struct gmenuitem *UNUSED(mi), GEvent *UNUSED(e)) {
    FontView *fv = (FontView *) GDrawGetUserData(gw);
    MMSet *mm = fv->b.sf->mm;

    if ( mm==NULL )
return;
    MMWizard(mm);
}