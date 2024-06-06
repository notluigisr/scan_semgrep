void ProtocolV2::connect() {
  ldout(cct, 1) << __func__ << dendl;
  state = START_CONNECT;
  pre_auth.enabled = true;
}