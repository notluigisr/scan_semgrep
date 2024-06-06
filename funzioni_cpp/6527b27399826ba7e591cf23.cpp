void IDLParserErrorContext::appendGenericCommandArguments(
    const BSONObj& commandPassthroughFields,
    const std::vector<StringData>& knownFields,
    BSONObjBuilder* builder) {

    for (const auto& element : commandPassthroughFields) {

        StringData name = element.fieldNameStringData();
        
        if (Command::isGenericArgument(name) &&
            std::find(knownFields.begin(), knownFields.end(), name) == knownFields.end()) {
            builder->append(element);
        }
    }
}