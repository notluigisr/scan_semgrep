void updateHandshakeState(QuicServerConnectionState& conn) {
  
  
  auto handshakeLayer = conn.serverHandshakeLayer;
  auto zeroRttReadCipher = handshakeLayer->getZeroRttReadCipher();
  auto zeroRttHeaderCipher = handshakeLayer->getZeroRttReadHeaderCipher();
  
  
  
  
  auto oneRttWriteCipher = handshakeLayer->getOneRttWriteCipher();
  
  auto oneRttReadCipher = handshakeLayer->getOneRttReadCipher();

  auto oneRttWriteHeaderCipher = handshakeLayer->getOneRttWriteHeaderCipher();
  auto oneRttReadHeaderCipher = handshakeLayer->getOneRttReadHeaderCipher();

  if (zeroRttReadCipher) {
    if (conn.qLogger) {
      conn.qLogger->addTransportStateUpdate(kDerivedZeroRttReadCipher);
    }
    QUIC_TRACE(fst_trace, conn, "STR");
    conn.readCodec->setZeroRttReadCipher(std::move(zeroRttReadCipher));
  }
  if (zeroRttHeaderCipher) {
    conn.readCodec->setZeroRttHeaderCipher(std::move(zeroRttHeaderCipher));
  }
  if (oneRttWriteHeaderCipher) {
    conn.oneRttWriteHeaderCipher = std::move(oneRttWriteHeaderCipher);
  }
  if (oneRttReadHeaderCipher) {
    conn.readCodec->setOneRttHeaderCipher(std::move(oneRttReadHeaderCipher));
  }

  if (oneRttWriteCipher) {
    if (conn.qLogger) {
      conn.qLogger->addTransportStateUpdate(kDerivedOneRttWriteCipher);
    }
    QUIC_TRACE(fst_trace, conn, "STR");
    CHECK(!conn.oneRttWriteCipher.get());
    conn.oneRttWriteCipher = std::move(oneRttWriteCipher);

    updatePacingOnKeyEstablished(conn);

    
    
    auto clientParams = handshakeLayer->getClientTransportParams();
    if (!clientParams) {
      throw QuicTransportException(
          "STR",
          TransportErrorCode::TRANSPORT_PARAMETER_ERROR);
    }
    processClientInitialParams(conn, std::move(*clientParams));
  }
  if (oneRttReadCipher) {
    if (conn.qLogger) {
      conn.qLogger->addTransportStateUpdate(kDerivedOneRttReadCipher);
    }
    QUIC_TRACE(fst_trace, conn, "STR");
    
    conn.writableBytesLimit = folly::none;
    conn.readCodec->setOneRttReadCipher(std::move(oneRttReadCipher));
  }
  auto handshakeReadCipher = handshakeLayer->getHandshakeReadCipher();
  auto handshakeReadHeaderCipher =
      handshakeLayer->getHandshakeReadHeaderCipher();
  if (handshakeReadCipher) {
    CHECK(handshakeReadHeaderCipher);
    conn.readCodec->setHandshakeReadCipher(std::move(handshakeReadCipher));
    conn.readCodec->setHandshakeHeaderCipher(
        std::move(handshakeReadHeaderCipher));
  }
  if (handshakeLayer->isHandshakeDone()) {
    CHECK(conn.oneRttWriteCipher);
    if (conn.version != QuicVersion::MVFST_D24 && !conn.sentHandshakeDone) {
      sendSimpleFrame(conn, HandshakeDoneFrame());
      conn.sentHandshakeDone = true;
    }
  }
}