R_API void r_bin_java_print_element_value_summary(RBinJavaElementValue *element_value) {
	RBinJavaCPTypeObj *obj;
	RBinJavaElementValue *ev_element = NULL;
	RListIter *iter = NULL, *iter_tmp = NULL;
	char *name;
	if (element_value == NULL) {
		eprintf ("STR");
		return;
	}
	name = ((RBinJavaElementValueMetas *) element_value->metas->type_info)->name;
	eprintf ("STR");
	eprintf ("STR", element_value->file_offset);
	eprintf ("STR", element_value->tag, name);
	switch (element_value->tag) {
	case R_BIN_JAVA_EV_TAG_BYTE:
	case R_BIN_JAVA_EV_TAG_CHAR:
	case R_BIN_JAVA_EV_TAG_DOUBLE:
	case R_BIN_JAVA_EV_TAG_FLOAT:
	case R_BIN_JAVA_EV_TAG_INT:
	case R_BIN_JAVA_EV_TAG_LONG:
	case R_BIN_JAVA_EV_TAG_SHORT:
	case R_BIN_JAVA_EV_TAG_BOOLEAN:
	case R_BIN_JAVA_EV_TAG_STRING:
		eprintf ("STR", element_value->value.const_value.const_value_idx);
		eprintf ("STR");
		obj = element_value->value.const_value.const_value_cp_obj;
		((RBinJavaCPTypeMetas *) obj->metas->type_info)->allocs->print_summary (obj);
		break;
	case R_BIN_JAVA_EV_TAG_ENUM:
		eprintf ("STR", element_value->value.enum_const_value.const_name_idx);
		eprintf ("STR", element_value->value.enum_const_value.type_name_idx);
		eprintf ("STR");
		obj = element_value->value.enum_const_value.const_name_cp_obj;
		((RBinJavaCPTypeMetas *) obj->metas->type_info)->allocs->print_summary (obj);
		eprintf ("STR");
		obj = element_value->value.enum_const_value.type_name_cp_obj;
		((RBinJavaCPTypeMetas *) obj->metas->type_info)->allocs->print_summary (obj);
		break;
	case R_BIN_JAVA_EV_TAG_CLASS:
		eprintf ("STR", element_value->value.class_value.class_info_idx);
		eprintf ("STR");
		obj = element_value->value.class_value.class_info_cp_obj;
		((RBinJavaCPTypeMetas *) obj->metas->type_info)->allocs->print_summary (obj);
		break;
	case R_BIN_JAVA_EV_TAG_ARRAY:
		eprintf ("STR", element_value->value.array_value.num_values);
		eprintf ("STR");
		r_list_foreach_safe (element_value->value.array_value.values, iter, iter_tmp, ev_element) {
			r_bin_java_print_element_value_summary (ev_element);
		}
		break;
	case R_BIN_JAVA_EV_TAG_ANNOTATION:
		eprintf ("STR");
		r_bin_java_print_annotation_summary (&element_value->value.annotation_value);
		break;
	default:
		
		break;
	}
}