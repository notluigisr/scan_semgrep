void Monitor::send_command(const entity_inst_t& inst,
			   const vector<string>& com)
{
  dout(10) << "STR" << com << dendl;
  MMonCommand *c = new MMonCommand(monmap->fsid);
  c->cmd = com;
  try_send_message(c, inst);
}