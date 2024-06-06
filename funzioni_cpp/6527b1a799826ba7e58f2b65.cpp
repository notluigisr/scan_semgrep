StartDA(qqueue_t *pThis)
{
	DEFiRet;
	uchar pszDAQName[128];

	ISOBJ_TYPE_assert(pThis, qqueue);

	
	CHKiRet(qqueueConstruct(&pThis->pqDA, QUEUETYPE_DISK , 1, 0, pThis->pConsumer));

	
	snprintf((char*) pszDAQName, sizeof(pszDAQName)/sizeof(uchar), "STR", obj.GetName((obj_t*) pThis));
	obj.SetName((obj_t*) pThis->pqDA, pszDAQName);

	
	pThis->pqDA->pqParent = pThis;

	CHKiRet(qqueueSetpUsr(pThis->pqDA, pThis->pUsr));
	CHKiRet(qqueueSetsizeOnDiskMax(pThis->pqDA, pThis->sizeOnDiskMax));
	CHKiRet(qqueueSetiDeqSlowdown(pThis->pqDA, pThis->iDeqSlowdown));
	CHKiRet(qqueueSetMaxFileSize(pThis->pqDA, pThis->iMaxFileSize));
	CHKiRet(qqueueSetFilePrefix(pThis->pqDA, pThis->pszFilePrefix, pThis->lenFilePrefix));
	CHKiRet(qqueueSetiPersistUpdCnt(pThis->pqDA, pThis->iPersistUpdCnt));
	CHKiRet(qqueueSetbSyncQueueFiles(pThis->pqDA, pThis->bSyncQueueFiles));
	CHKiRet(qqueueSettoActShutdown(pThis->pqDA, pThis->toActShutdown));
	CHKiRet(qqueueSettoEnq(pThis->pqDA, pThis->toEnq));
	CHKiRet(qqueueSetiDeqtWinFromHr(pThis->pqDA, pThis->iDeqtWinFromHr));
	CHKiRet(qqueueSetiDeqtWinToHr(pThis->pqDA, pThis->iDeqtWinToHr));
	CHKiRet(qqueueSettoQShutdown(pThis->pqDA, pThis->toQShutdown));
	CHKiRet(qqueueSetiHighWtrMrk(pThis->pqDA, 0));
	CHKiRet(qqueueSetiDiscardMrk(pThis->pqDA, 0));

	iRet = qqueueStart(pThis->pqDA);
	
	if(iRet != RS_RET_OK && iRet != RS_RET_FILE_NOT_FOUND) {
		errno = 0; 
		errmsg.LogError(errno, iRet, "STR");
		pThis->bIsDA = 0;	
		FINALIZE; 
	}

	DBGOPRINT((obj_t*) pThis, "STR",
		  qqueueGetID(pThis->pqDA));

finalize_it:
	if(iRet != RS_RET_OK) {
		if(pThis->pqDA != NULL) {
			qqueueDestruct(&pThis->pqDA);
		}
		DBGOPRINT((obj_t*) pThis, "STR", iRet);
		pThis->bIsDA = 0;
	}

	RETiRet;
}