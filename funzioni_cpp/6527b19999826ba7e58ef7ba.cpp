dns_check_entry(u8_t i)
{
  err_t err;
  struct dns_table_entry *entry = &dns_table[i];

  LWIP_ASSERT("STR", i < DNS_TABLE_SIZE);

  switch (entry->state) {

    case DNS_STATE_NEW: {
      u16_t txid;
      
      txid = dns_create_txid();
      entry->txid = txid;
      entry->state   = DNS_STATE_ASKING;
      entry->numdns  = 0;
      entry->tmr     = 1;
      entry->retries = 0;

      
      err = dns_send(entry->numdns, entry->name, txid);
      if (err != ERR_OK) {
        LWIP_DEBUGF(DNS_DEBUG | LWIP_DBG_LEVEL_WARNING,
                    ("STR", lwip_strerr(err)));
      }
      break;
    }

    case DNS_STATE_ASKING:
      if (--entry->tmr == 0) {
        if (++entry->retries == DNS_MAX_RETRIES) {
          if ((entry->numdns+1<DNS_MAX_SERVERS) && !ip_addr_isany(&dns_servers[entry->numdns+1])) {
            
            entry->numdns++;
            entry->tmr     = 1;
            entry->retries = 0;
            break;
          } else {
            LWIP_DEBUGF(DNS_DEBUG, ("STR", entry->name));
            
            dns_call_found(i, NULL);
            
            entry->state   = DNS_STATE_UNUSED;
            break;
          }
        }

        
        entry->tmr = entry->retries;

        
        err = dns_send(entry->numdns, entry->name, entry->txid);
        if (err != ERR_OK) {
          LWIP_DEBUGF(DNS_DEBUG | LWIP_DBG_LEVEL_WARNING,
                      ("STR", lwip_strerr(err)));
        }
      }
      break;
    case DNS_STATE_DONE:
      
      if ((entry->ttl == 0) || (--entry->ttl == 0)) {
        LWIP_DEBUGF(DNS_DEBUG, ("STR", entry->name));
        
        entry->state = DNS_STATE_UNUSED;
      }
      break;
    case DNS_STATE_UNUSED:
      
      break;
    default:
      LWIP_ASSERT("STR", 0);
      break;
  }
}