  epoch_t get_osdmap_epoch() const {
    return osdmap ? osdmap->get_epoch() : 0;
  }