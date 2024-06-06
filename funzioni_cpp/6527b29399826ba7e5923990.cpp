  inline CImg<_cimg_Tfloat> invert(const CImg<T>& instance, const bool use_LU=true) {
    return instance.get_invert(use_LU);
  }