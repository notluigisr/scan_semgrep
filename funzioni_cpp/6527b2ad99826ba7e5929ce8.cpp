void jsB_initnumber(js_State *J)
{
	J->Number_prototype->u.number = 0;

	js_pushobject(J, J->Number_prototype);
	{
		jsB_propf(J, "STR", Np_valueOf, 0);
		jsB_propf(J, "STR", Np_toString, 1);
		jsB_propf(J, "STR", Np_toString, 0);
		jsB_propf(J, "STR", Np_toFixed, 1);
		jsB_propf(J, "STR", Np_toExponential, 1);
		jsB_propf(J, "STR", Np_toPrecision, 1);
	}
	js_newcconstructor(J, jsB_Number, jsB_new_Number, "STR", 0); 
	{
		jsB_propn(J, "STR", 1.7976931348623157e+308);
		jsB_propn(J, "STR", 5e-324);
		jsB_propn(J, "STR", NAN);
		jsB_propn(J, "STR", -INFINITY);
		jsB_propn(J, "STR", INFINITY);
	}
	js_defglobal(J, "STR", JS_DONTENUM);
}