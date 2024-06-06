bool ParseMessageSetItemImpl(io::CodedInputStream* input, MS ms) {
  
  
  

  uint32_t last_type_id = 0;

  
  
  std::string message_data;

  while (true) {
    const uint32_t tag = input->ReadTagNoLastTag();
    if (tag == 0) return false;

    switch (tag) {
      case WireFormatLite::kMessageSetTypeIdTag: {
        uint32_t type_id;
        if (!input->ReadVarint32(&type_id)) return false;
        last_type_id = type_id;

        if (!message_data.empty()) {
          
          
          io::CodedInputStream sub_input(
              reinterpret_cast<const uint8_t*>(message_data.data()),
              static_cast<int>(message_data.size()));
          sub_input.SetRecursionLimit(input->RecursionBudget());
          if (!ms.ParseField(last_type_id, &sub_input)) {
            return false;
          }
          message_data.clear();
        }

        break;
      }

      case WireFormatLite::kMessageSetMessageTag: {
        if (last_type_id == 0) {
          
          uint32_t length;
          if (!input->ReadVarint32(&length)) return false;
          if (static_cast<int32_t>(length) < 0) return false;
          uint32_t size = static_cast<uint32_t>(
              length + io::CodedOutputStream::VarintSize32(length));
          message_data.resize(size);
          auto ptr = reinterpret_cast<uint8_t*>(&message_data[0]);
          ptr = io::CodedOutputStream::WriteVarint32ToArray(length, ptr);
          if (!input->ReadRaw(ptr, length)) return false;
        } else {
          
          if (!ms.ParseField(last_type_id, input)) {
            return false;
          }
        }

        break;
      }

      case WireFormatLite::kMessageSetItemEndTag: {
        return true;
      }

      default: {
        if (!ms.SkipField(tag, input)) return false;
      }
    }
  }
}