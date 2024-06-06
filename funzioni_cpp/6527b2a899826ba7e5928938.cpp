  ::testing::AssertionResult operator()(const char *, const T &value) const {
    ::testing::AssertionResult result = check_write<char>(value, "STR");
    return result ? check_write<wchar_t>(value, "STR") : result;
  }