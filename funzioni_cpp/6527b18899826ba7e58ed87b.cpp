Status RoleGraph::getBSONForRole(RoleGraph* graph,
                                 const RoleName& roleName,
                                 mutablebson::Element result) try {
    if (!graph->roleExists(roleName)) {
        return Status(ErrorCodes::RoleNotFound,
                      mongoutils::str::stream() << roleName.getFullName()
                                                << "STR");
    }
    std::string id = mongoutils::str::stream() << roleName.getDB() << "STR" << roleName.getRole();
    uassertStatusOK(result.appendString("STR", id));
    uassertStatusOK(
        result.appendString(AuthorizationManager::ROLE_NAME_FIELD_NAME, roleName.getRole()));
    uassertStatusOK(
        result.appendString(AuthorizationManager::ROLE_DB_FIELD_NAME, roleName.getDB()));

    
    mutablebson::Element privilegesArrayElement =
        result.getDocument().makeElementArray("STR");
    uassertStatusOK(result.pushBack(privilegesArrayElement));
    const PrivilegeVector& privileges = graph->getDirectPrivileges(roleName);
    uassertStatusOK(Privilege::getBSONForPrivileges(privileges, privilegesArrayElement));

    
    mutablebson::Element rolesArrayElement = result.getDocument().makeElementArray("STR");
    uassertStatusOK(result.pushBack(rolesArrayElement));
    for (RoleNameIterator roles = graph->getDirectSubordinates(roleName); roles.more();
         roles.next()) {
        const RoleName& subRole = roles.get();
        mutablebson::Element roleObj = result.getDocument().makeElementObject("");
        uassertStatusOK(
            roleObj.appendString(AuthorizationManager::ROLE_NAME_FIELD_NAME, subRole.getRole()));
        uassertStatusOK(
            roleObj.appendString(AuthorizationManager::ROLE_DB_FIELD_NAME, subRole.getDB()));
        uassertStatusOK(rolesArrayElement.pushBack(roleObj));
    }

    return Status::OK();
} catch (...) {