static void renameReloadSchema(Parse *pParse, int iDb){
  Vdbe *v = pParse->pVdbe;
  if( v ){
    sqlite3ChangeCookie(pParse, iDb);
    sqlite3VdbeAddParseSchemaOp(pParse->pVdbe, iDb, 0);
    if( iDb!=1 ) sqlite3VdbeAddParseSchemaOp(pParse->pVdbe, 1, 0);
  }
}