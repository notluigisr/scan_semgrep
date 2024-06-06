    Network::ListenSocketFactory& listenSocketFactory() override {
      return *parent_.socket_factory_;
    }