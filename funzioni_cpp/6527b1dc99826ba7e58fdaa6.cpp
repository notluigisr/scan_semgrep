void ServerHello::Process(input_buffer& input, SSL& ssl)
{
    if (input.get_error()) {
        ssl.SetError(bad_input);
        return;
    }

    if (ssl.GetMultiProtocol()) {   
        if (ssl.isTLS() && server_version_.minor_ < 1)
            
            ssl.useSecurity().use_connection().TurnOffTLS();
        else if (ssl.isTLSv1_1() && server_version_.minor_ == 1)
            
            ssl.useSecurity().use_connection().TurnOffTLS1_1();
    }
    else if (ssl.isTLSv1_1() && server_version_.minor_ < 2) {
        ssl.SetError(badVersion_error);
        return;
    }
    else if (ssl.isTLS() && server_version_.minor_ < 1) {
        ssl.SetError(badVersion_error);
        return;
    }
    else if (!ssl.isTLS() && (server_version_.major_ == 3 &&
                              server_version_.minor_ >= 1)) {
        ssl.SetError(badVersion_error);
        return;
    }
    ssl.set_pending(cipher_suite_[1]);
    ssl.set_random(random_, server_end);
    if (id_len_)
        ssl.set_sessionID(session_id_);
    else
        ssl.useSecurity().use_connection().sessionID_Set_ = false;

    if (ssl.getSecurity().get_resuming()) {
        if (memcmp(session_id_, ssl.getSecurity().get_resume().GetID(),
                   ID_LEN) == 0) {
            ssl.set_masterSecret(ssl.getSecurity().get_resume().GetSecret());
            if (ssl.isTLS())
                ssl.deriveTLSKeys();
            else
                ssl.deriveKeys();
            ssl.useStates().useClient() = serverHelloDoneComplete;
            return;
        }
        else {
            ssl.useSecurity().set_resuming(false);
            ssl.useLog().Trace("STR");
        }
    }

    if (ssl.CompressionOn() && !compression_method_)
        ssl.UnSetCompression(); 

    ssl.useStates().useClient() = serverHelloComplete;
}