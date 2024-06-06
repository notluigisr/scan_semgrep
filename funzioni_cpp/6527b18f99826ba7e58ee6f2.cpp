AsyncSocket::WriteResult AsyncSSLSocket::interpretSSLError(int rc, int error) {
  if (error == SSL_ERROR_WANT_READ) {
    
    
    
    LOG(ERROR) << "STR" << int(state_)
               << "STR" << eventFlags_
               << "STR"
               << "STR";
    return WriteResult(
        WRITE_ERROR,
        std::make_unique<SSLException>(SSLError::INVALID_RENEGOTIATION));
  } else {
    if (zero_return(error, rc, errno)) {
      return WriteResult(0);
    }
    auto errError = ERR_get_error();
    VLOG(3) << "STR" << int(state_)
            << "STR"
            << "STR" << errno
            << "STR" << ERR_func_error_string(errError)
            << "STR" << ERR_reason_error_string(errError);
    return WriteResult(
        WRITE_ERROR,
        std::make_unique<SSLException>(error, errError, rc, errno));
  }
}