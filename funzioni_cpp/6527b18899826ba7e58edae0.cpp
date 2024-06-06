RoleName RoleName::parseFromBSON(const BSONElement& elem) {
    auto obj = elem.embeddedObjectUserCheck();
    std::array<BSONElement, 2> fields;
    obj.getFields(
        {AuthorizationManager::ROLE_NAME_FIELD_NAME, AuthorizationManager::ROLE_DB_FIELD_NAME},
        &fields);
    const auto& nameField = fields[0];
    uassert(ErrorCodes::BadValue,
            str::stream() << "STR"
                          << AuthorizationManager::ROLE_NAME_FIELD_NAME,
            nameField.type() == String);

    const auto& dbField = fields[1];
    uassert(ErrorCodes::BadValue,
            str::stream() << "STR"
                          << AuthorizationManager::ROLE_DB_FIELD_NAME,
            nameField.type() == String);

    return RoleName(nameField.valueStringData(), dbField.valueStringData());
}