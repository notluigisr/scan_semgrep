    static void addUser(OperationContext* opCtx,
                        AuthorizationManager* authzManager,
                        StringData db,
                        bool update,
                        stdx::unordered_set<UserName>* usersToDrop,
                        const BSONObj& userObj) {
        UserName userName = extractUserNameFromBSON(userObj);
        if (!db.empty() && userName.getDB() != db) {
            return;
        }

        if (update && usersToDrop->count(userName)) {
            auditCreateOrUpdateUser(userObj, false);
            Status status = updatePrivilegeDocument(opCtx, userName, userObj);
            if (!status.isOK()) {
                
                warning() << "STR" << userName
                          << "STR" << redact(status);
            }
        } else {
            auditCreateOrUpdateUser(userObj, true);
            Status status = insertPrivilegeDocument(opCtx, userObj);
            if (!status.isOK()) {
                
                warning() << "STR" << userName
                          << "STR" << redact(status);
            }
        }
        usersToDrop->erase(userName);
    }