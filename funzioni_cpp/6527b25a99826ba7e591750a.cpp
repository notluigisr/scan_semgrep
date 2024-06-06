TEST_F(Http1ClientConnectionImplTest, 204Response) {
  initialize();

  NiceMock<MockResponseDecoder> response_decoder;
  Http::RequestEncoder& request_encoder = codec_->newStream(response_decoder);
  TestRequestHeaderMapImpl headers{{"STR"}};
  request_encoder.encodeHeaders(headers, true);

  EXPECT_CALL(response_decoder, decodeHeaders_(_, true));
  Buffer::OwnedImpl response("STR");
  auto status = codec_->dispatch(response);
  EXPECT_TRUE(status.ok());
}