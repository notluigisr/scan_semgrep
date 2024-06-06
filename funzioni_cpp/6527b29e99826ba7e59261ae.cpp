DEFUN (show_ip_bgp_rsclient_summary,
       show_ip_bgp_rsclient_summary_cmd,
       "STR",
       SHOW_STR
       IP_STR
       BGP_STR
       "STR"
       "STR")
{
  return bgp_show_rsclient_summary_vty (vty, NULL, AFI_IP, SAFI_UNICAST);
}