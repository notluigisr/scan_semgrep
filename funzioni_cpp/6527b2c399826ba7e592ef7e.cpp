inline void WireFormatLite::WriteEnumNoTag(int value,
                                           io::CodedOutputStream* output) {
  output->WriteVarint32SignExtended(value);
}