int sqlite3Fts3PendingTermsFlush(Fts3Table *p){
  int rc = SQLITE_OK;
  int i;
        
  for(i=0; rc==SQLITE_OK && i<p->nIndex; i++){
    rc = fts3SegmentMerge(p, p->iPrevLangid, i, FTS3_SEGCURSOR_PENDING);
    if( rc==SQLITE_DONE ) rc = SQLITE_OK;
  }
  sqlite3Fts3PendingTermsClear(p);

  
  if( rc==SQLITE_OK && p->bHasStat
   && p->nAutoincrmerge==0xff && p->nLeafAdd>0
  ){
    sqlite3_stmt *pStmt = 0;
    rc = fts3SqlStmt(p, SQL_SELECT_STAT, &pStmt, 0);
    if( rc==SQLITE_OK ){
      sqlite3_bind_int(pStmt, 1, FTS_STAT_AUTOINCRMERGE);
      rc = sqlite3_step(pStmt);
      if( rc==SQLITE_ROW ){
        p->nAutoincrmerge = sqlite3_column_int(pStmt, 0);
        if( p->nAutoincrmerge==1 ) p->nAutoincrmerge = 8;
      }else if( rc==SQLITE_DONE ){
        p->nAutoincrmerge = 0;
      }
      rc = sqlite3_reset(pStmt);
    }
  }
  return rc;
}