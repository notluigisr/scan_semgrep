  const HeaderEntry& pathHeaderEntry(const std::string& path_value) {
    headers_.setPath(path_value);
    return *headers_.Path();
  }