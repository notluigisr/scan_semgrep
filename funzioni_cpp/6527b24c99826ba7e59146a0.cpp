Track* Segment::AddTrack(int32_t number) {
  Track* const track = new (std::nothrow) Track(&seed_);  

  if (!track)
    return NULL;

  if (!tracks_.AddTrack(track, number)) {
    delete track;
    return NULL;
  }

  return track;
}