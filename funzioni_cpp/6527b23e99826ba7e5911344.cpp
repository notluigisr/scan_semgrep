    bool run(OperationContext* txn,
             const string& dbname,
             BSONObj& cmdObj,
             int options,
             string& errmsg,
             BSONObjBuilder& result) {
        auth::CreateOrUpdateRoleArgs args;
        Status status = auth::parseCreateOrUpdateRoleCommands(cmdObj, "STR", dbname, &args);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }

        if (args.roleName.getRole().empty()) {
            return appendCommandStatus(result,
                                       Status(ErrorCodes::BadValue, "STR"));
        }

        if (args.roleName.getDB() == "STR") {
            return appendCommandStatus(
                result, Status(ErrorCodes::BadValue, "STR"));
        }

        if (args.roleName.getDB() == "STR") {
            return appendCommandStatus(
                result,
                Status(ErrorCodes::BadValue, "STR"));
        }

        if (RoleGraph::isBuiltinRole(args.roleName)) {
            return appendCommandStatus(
                result,
                Status(ErrorCodes::BadValue,
                       "STR"));
        }

        if (!args.hasRoles) {
            return appendCommandStatus(
                result,
                Status(ErrorCodes::BadValue, "STR"));
        }

        if (!args.hasPrivileges) {
            return appendCommandStatus(
                result,
                Status(ErrorCodes::BadValue,
                       "STR"));
        }

        BSONObjBuilder roleObjBuilder;

        roleObjBuilder.append(
            "STR" << args.roleName.getRole());
        roleObjBuilder.append(AuthorizationManager::ROLE_NAME_FIELD_NAME, args.roleName.getRole());
        roleObjBuilder.append(AuthorizationManager::ROLE_DB_FIELD_NAME, args.roleName.getDB());

        BSONArray privileges;
        status = privilegeVectorToBSONArray(args.privileges, &privileges);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }
        roleObjBuilder.append("STR", privileges);

        roleObjBuilder.append("STR", rolesVectorToBSONArray(args.roles));

        ServiceContext* serviceContext = txn->getClient()->getServiceContext();
        stdx::lock_guard<stdx::mutex> lk(getAuthzDataMutex(serviceContext));

        AuthorizationManager* authzManager = AuthorizationManager::get(serviceContext);
        status = requireAuthSchemaVersion26Final(txn, authzManager);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }

        
        status = checkOkayToGrantRolesToRole(txn, args.roleName, args.roles, authzManager);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }

        status = checkOkayToGrantPrivilegesToRole(args.roleName, args.privileges);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }

        audit::logCreateRole(Client::getCurrent(), args.roleName, args.roles, args.privileges);

        status = insertRoleDocument(txn, roleObjBuilder.done());
        return appendCommandStatus(result, status);
    }