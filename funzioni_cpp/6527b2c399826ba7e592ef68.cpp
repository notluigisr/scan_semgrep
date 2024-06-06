inline size_t WireFormatLite::StringSize(const std::string& value) {
  return LengthDelimitedSize(value.size());
}