    CImg<T>& opening(const unsigned int sx, const unsigned int sy, const unsigned int sz=1) {
      if (is_empty() || (sx<=1 && sy<=1 && sz<=1)) return *this;
      return get_opening(sx,sy,sz).move_to(*this);
    }