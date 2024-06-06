Value ExpressionIndexOfBytes::evaluate(const Document& root, Variables* variables) const {
    Value stringArg = _children[0]->evaluate(root, variables);

    if (stringArg.nullish()) {
        return Value(BSONNULL);
    }

    uassert(40091,
            str::stream() << "STR"
                          << typeName(stringArg.getType()),
            stringArg.getType() == String);
    const std::string& input = stringArg.getString();

    Value tokenArg = _children[1]->evaluate(root, variables);
    uassert(40092,
            str::stream() << "STR"
                          << typeName(tokenArg.getType()),
            tokenArg.getType() == String);
    const std::string& token = tokenArg.getString();

    size_t startIndex = 0;
    if (_children.size() > 2) {
        Value startIndexArg = _children[2]->evaluate(root, variables);
        uassertIfNotIntegralAndNonNegative(startIndexArg, getOpName(), "STR");
        startIndex = static_cast<size_t>(startIndexArg.coerceToInt());
    }

    size_t endIndex = input.size();
    if (_children.size() > 3) {
        Value endIndexArg = _children[3]->evaluate(root, variables);
        uassertIfNotIntegralAndNonNegative(endIndexArg, getOpName(), "STR");
        
        endIndex = std::min(input.size(), static_cast<size_t>(endIndexArg.coerceToInt()));
    }

    if (startIndex > input.length() || endIndex < startIndex) {
        return Value(-1);
    }

    size_t position = input.substr(0, endIndex).find(token, startIndex);
    if (position == std::string::npos) {
        return Value(-1);
    }

    return Value(static_cast<int>(position));
}