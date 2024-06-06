TEST_F(StreamInfoImplTest, MiscSettersAndGetters) {
  {
    StreamInfoImpl stream_info(Http::Protocol::Http2, test_time_.timeSystem(), nullptr);

    EXPECT_EQ(nullptr, stream_info.upstreamInfo());
    EXPECT_EQ(Http::Protocol::Http2, stream_info.protocol().value());
    stream_info.setUpstreamInfo(std::make_shared<UpstreamInfoImpl>());

    stream_info.protocol(Http::Protocol::Http10);
    EXPECT_EQ(Http::Protocol::Http10, stream_info.protocol().value());

    EXPECT_FALSE(stream_info.responseCode());
    stream_info.response_code_ = 200;
    ASSERT_TRUE(stream_info.responseCode());
    EXPECT_EQ(200, stream_info.responseCode().value());

    EXPECT_FALSE(stream_info.attemptCount().has_value());
    stream_info.setAttemptCount(93);
    ASSERT_TRUE(stream_info.attemptCount().has_value());
    EXPECT_EQ(stream_info.attemptCount().value(), 93);

    EXPECT_FALSE(stream_info.responseCodeDetails().has_value());
    stream_info.setResponseCodeDetails(ResponseCodeDetails::get().ViaUpstream);
    ASSERT_TRUE(stream_info.responseCodeDetails().has_value());
    EXPECT_EQ(ResponseCodeDetails::get().ViaUpstream, stream_info.responseCodeDetails().value());

    EXPECT_FALSE(stream_info.connectionTerminationDetails().has_value());
    stream_info.setConnectionTerminationDetails("STR");
    ASSERT_TRUE(stream_info.connectionTerminationDetails().has_value());
    EXPECT_EQ("STR", stream_info.connectionTerminationDetails().value());

    EXPECT_EQ(nullptr, stream_info.upstreamInfo()->upstreamHost());
    Upstream::HostDescriptionConstSharedPtr host(new NiceMock<Upstream::MockHostDescription>());
    stream_info.upstreamInfo()->setUpstreamHost(host);
    EXPECT_EQ(host, stream_info.upstreamInfo()->upstreamHost());

    EXPECT_FALSE(stream_info.healthCheck());
    stream_info.healthCheck(true);
    EXPECT_TRUE(stream_info.healthCheck());

    EXPECT_EQ(nullptr, stream_info.route());
    std::shared_ptr<NiceMock<Router::MockRoute>> route =
        std::make_shared<NiceMock<Router::MockRoute>>();
    stream_info.route_ = route;
    EXPECT_EQ(route, stream_info.route());

    stream_info.filterState()->setData("STR", std::make_unique<TestIntAccessor>(1),
                                       FilterState::StateType::ReadOnly,
                                       FilterState::LifeSpan::FilterChain);
    EXPECT_EQ(1, stream_info.filterState()->getDataReadOnly<TestIntAccessor>("STR")->access());

    stream_info.upstreamInfo()->setUpstreamFilterState(stream_info.filterState());
    EXPECT_EQ(1, stream_info.upstreamInfo()
                     ->upstreamFilterState()
                     ->getDataReadOnly<TestIntAccessor>("STR")
                     ->access());

    EXPECT_EQ(absl::nullopt, stream_info.upstreamClusterInfo());
    Upstream::ClusterInfoConstSharedPtr cluster_info(new NiceMock<Upstream::MockClusterInfo>());
    stream_info.setUpstreamClusterInfo(cluster_info);
    EXPECT_NE(absl::nullopt, stream_info.upstreamClusterInfo());
    EXPECT_EQ("STR", stream_info.upstreamClusterInfo().value()->name());

    const std::string session_id =
        "STR";
    auto ssl_info = std::make_shared<Ssl::MockConnectionInfo>();
    EXPECT_CALL(*ssl_info, sessionId()).WillRepeatedly(testing::ReturnRef(session_id));
    stream_info.upstreamInfo()->setUpstreamSslConnection(ssl_info);
    EXPECT_EQ(session_id, stream_info.upstreamInfo()->upstreamSslConnection()->sessionId());

    EXPECT_FALSE(stream_info.upstreamInfo()->upstreamConnectionId().has_value());
    stream_info.upstreamInfo()->setUpstreamConnectionId(12345);
    ASSERT_TRUE(stream_info.upstreamInfo()->upstreamConnectionId().has_value());
    EXPECT_EQ(12345, stream_info.upstreamInfo()->upstreamConnectionId().value());

    EXPECT_FALSE(stream_info.upstreamInfo()->upstreamInterfaceName().has_value());
    stream_info.upstreamInfo()->setUpstreamInterfaceName("STR");
    ASSERT_TRUE(stream_info.upstreamInfo()->upstreamInterfaceName().has_value());
    EXPECT_EQ("STR", stream_info.upstreamInfo()->upstreamInterfaceName().value());

    std::shared_ptr<UpstreamInfo> new_info = std::make_shared<UpstreamInfoImpl>();
    EXPECT_NE(stream_info.upstreamInfo(), new_info);
    stream_info.setUpstreamInfo(new_info);
    EXPECT_EQ(stream_info.upstreamInfo(), new_info);
  }
}