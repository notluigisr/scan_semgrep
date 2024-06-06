folly::Optional<TLSMessage> EncryptedReadRecordLayer::read(
    folly::IOBufQueue& buf) {
  auto decryptedBuf = getDecryptedBuf(buf);
  if (!decryptedBuf) {
    return folly::none;
  }

  TLSMessage msg;
  
  
  
  auto currentBuf = decryptedBuf->get();
  bool nonZeroFound = false;
  do {
    currentBuf = currentBuf->prev();
    size_t i = currentBuf->length();
    while (i > 0 && !nonZeroFound) {
      nonZeroFound = (currentBuf->data()[i - 1] != 0);
      i--;
    }
    if (nonZeroFound) {
      msg.type = static_cast<ContentType>(currentBuf->data()[i]);
    }
    currentBuf->trimEnd(currentBuf->length() - i);
  } while (!nonZeroFound && currentBuf != decryptedBuf->get());
  if (!nonZeroFound) {
    throw std::runtime_error("STR");
  }
  msg.fragment = std::move(*decryptedBuf);

  switch (msg.type) {
    case ContentType::handshake:
    case ContentType::alert:
    case ContentType::application_data:
      break;
    default:
      throw std::runtime_error(folly::to<std::string>(
          "STR",
          static_cast<ContentTypeType>(msg.type)));
  }

  if (!msg.fragment) {
    if (msg.type == ContentType::application_data) {
      msg.fragment = folly::IOBuf::create(0);
    } else {
      throw std::runtime_error("STR");
    }
  }

  return msg;
}