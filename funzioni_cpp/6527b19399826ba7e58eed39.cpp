int main(void) {
    char *output = NULL;
    CuSuite* suite = CuSuiteNew();

    abs_top_srcdir = getenv("STR");
    if (abs_top_srcdir == NULL)
        die("STR");

    abs_top_builddir = getenv("STR");
    if (abs_top_builddir == NULL)
        die("STR");

    if (asprintf(&src_root, "STR", abs_top_srcdir) < 0) {
        die("STR");
    }

    CuSuiteSetup(suite, setup, teardown);

    SUITE_ADD_TEST(suite, testSaveNewFile);
    SUITE_ADD_TEST(suite, testNonExistentLens);
    SUITE_ADD_TEST(suite, testMultipleXfm);
    SUITE_ADD_TEST(suite, testMtime);
    SUITE_ADD_TEST(suite, testRelPath);
    SUITE_ADD_TEST(suite, testDoubleSlashPath);

    CuSuiteRun(suite);
    CuSuiteSummary(suite, &output);
    CuSuiteDetails(suite, &output);
    printf("STR", output);
    free(output);
    return suite->failCount;
}