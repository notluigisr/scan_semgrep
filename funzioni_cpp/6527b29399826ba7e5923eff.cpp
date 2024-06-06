START_TEST(input_prop_parser)
{
	struct parser_test_val {
		const char *prop;
		bool success;
		size_t nvals;
		uint32_t values[20];
	} tests[] = {
		{ "STR", true, 1, {INPUT_PROP_BUTTONPAD}},
		{ "STR", true, 2,
			{ INPUT_PROP_BUTTONPAD,
			  INPUT_PROP_POINTER }},
		{ "STR", true, 3,
			{ INPUT_PROP_BUTTONPAD,
			  INPUT_PROP_POINTER,
			  INPUT_PROP_SEMI_MT }},
		{ .prop = "", .success = false },
		{ .prop = "STR", .success = false },
		{ .prop = "STR", .success = false },
		{ .prop = "STR", .success = false },
		{ .prop = "STR", .success = false },
		{ .prop = "STR", .success = false },
		{ .prop = "STR", .success = false },
		{ .prop = NULL },
	};
	struct parser_test_val *t;

	for (int i = 0; tests[i].prop; i++) {
		bool success;
		uint32_t props[32];
		size_t nprops = ARRAY_LENGTH(props);

		t = &tests[i];
		success = parse_input_prop_property(t->prop, props, &nprops);
		ck_assert(success == t->success);
		if (!success)
			continue;

		ck_assert_int_eq(nprops, t->nvals);
		for (size_t j = 0; j < t->nvals; j++) {
			ck_assert_int_eq(t->values[j], props[j]);
		}
	}
}