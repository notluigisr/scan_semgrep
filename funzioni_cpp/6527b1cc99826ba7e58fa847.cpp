print_p2r_setparameters (const unsigned char *msg, size_t msglen)
{
  print_p2r_header ("STR", msg, msglen);
  if (msglen < 10)
    return;
  DEBUGOUT_1 ("STR", msg[7]);
  print_pr_data (msg, msglen, 8);
}