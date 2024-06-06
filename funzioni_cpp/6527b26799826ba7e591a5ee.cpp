Value ExpressionLet::serialize(bool explain) const {
    MutableDocument vars;
    for (VariableMap::const_iterator it = _variables.begin(), end = _variables.end(); it != end;
         ++it) {
        vars[it->second.name] = it->second.expression->serialize(explain);
    }

    return Value(
        DOC("STR" << _subExpression->serialize(explain))));
}