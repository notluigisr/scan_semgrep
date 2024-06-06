TEST_P(Http2CodecImplTest, ResponseHeadersFlood) {
  initialize();

  TestRequestHeaderMapImpl request_headers;
  HttpTestUtility::addDefaultHeaders(request_headers);
  EXPECT_CALL(request_decoder_, decodeHeaders_(_, false));
  request_encoder_->encodeHeaders(request_headers, false);

  int frame_count = 0;
  Buffer::OwnedImpl buffer;
  ON_CALL(server_connection_, write(_, _))
      .WillByDefault(Invoke([&buffer, &frame_count](Buffer::Instance& frame, bool) {
        ++frame_count;
        buffer.move(frame);
      }));

  TestResponseHeaderMapImpl response_headers{{"STR"}};
  for (uint32_t i = 0; i < CommonUtility::OptionsLimits::DEFAULT_MAX_OUTBOUND_FRAMES + 1; ++i) {
    EXPECT_NO_THROW(response_encoder_->encodeHeaders(response_headers, false));
  }
  
  
  EXPECT_EQ(0, nghttp2_submit_ping(client_->session(), NGHTTP2_FLAG_NONE, nullptr));
  EXPECT_THROW(client_->sendPendingFrames(), ServerCodecError);

  EXPECT_EQ(frame_count, CommonUtility::OptionsLimits::DEFAULT_MAX_OUTBOUND_FRAMES + 1);
  EXPECT_EQ(1, stats_store_.counter("STR").value());
}