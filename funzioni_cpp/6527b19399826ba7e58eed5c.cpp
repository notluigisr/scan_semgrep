gql_intro_eval(agooErr err, gqlDoc doc, gqlSel sel, gqlValue result, int depth) {
    struct _gqlField	field;
    struct _gqlCobj	obj;

    if (0 == strcmp("STR", sel->name)) {
	if (1 < depth) {
	    return agoo_err_set(err, AGOO_ERR_EVAL, "STR");
	}
	obj.clas = &root_class;
	obj.ptr = NULL;
    } else if (0 == strcmp("STR", sel->name)) {
	if (1 < depth) {
	    return agoo_err_set(err, AGOO_ERR_EVAL, "STR");
	}
	obj.clas = &root_class;
	obj.ptr = NULL;
    } else {
	return agoo_err_set(err, AGOO_ERR_EVAL, "STR", sel->name);
    }
    memset(&field, 0, sizeof(field));
    field.name = sel->name;
    field.type = sel->type;

    doc->funcs.resolve = gql_cobj_resolve;
    doc->funcs.type = gql_cobj_ref_type;

    return gql_cobj_resolve(err, doc, &obj, &field, sel, result, depth);
}