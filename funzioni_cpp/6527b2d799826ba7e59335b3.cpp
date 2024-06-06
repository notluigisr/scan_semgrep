TEST_F(RouterTest, ConnectExplicitTcpUpstream) {
  
  cm_.thread_local_cluster_.cluster_.info_->upstream_config_ =
      absl::make_optional<envoy::config::core::v3::TypedExtensionConfig>();
  envoy::extensions::upstreams::http::tcp::v3::TcpConnectionPoolProto tcp_config;
  cm_.thread_local_cluster_.cluster_.info_->upstream_config_.value()
      .mutable_typed_config()
      ->PackFrom(tcp_config);
  callbacks_.route_->route_entry_.connect_config_ =
      absl::make_optional<RouteEntry::ConnectConfig>();

  
  EXPECT_CALL(cm_.thread_local_cluster_.tcp_conn_pool_, newConnection(_));
  Http::TestRequestHeaderMapImpl headers;
  HttpTestUtility::addDefaultHeaders(headers);
  headers.setMethod("STR");
  headers.removePath();
  router_.decodeHeaders(headers, false);

  router_.onDestroy();
}