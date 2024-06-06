    CImg<T>& _load_ascii(std::FILE *const file, const char *const filename) {
      if (!file && !filename)
        throw CImgArgumentException(_cimg_instance
                                    "STR",
                                    cimg_instance);

      std::FILE *const nfile = file?file:cimg::fopen(filename,"STR");
      CImg<charT> line(256); *line = 0;
      int err = std::fscanf(nfile,"STR",line._data);
      unsigned int dx = 0, dy = 1, dz = 1, dc = 1;
      cimg_sscanf(line,"STR",&dx,&dy,&dz,&dc);
      err = std::fscanf(nfile,"STR");
      if (!dx || !dy || !dz || !dc) {
        if (!file) cimg::fclose(nfile);
        throw CImgIOException(_cimg_instance
                              "STR"
                              "STR",
                              cimg_instance,
                              filename?filename:"STR",dx,dy,dz,dc);
      }
      assign(dx,dy,dz,dc);
      const ulongT siz = size();
      ulongT off = 0;
      double val;
      T *ptr = _data;
      for (err = 1, off = 0; off<siz && err==1; ++off) {
        err = std::fscanf(nfile,"STR",&val);
        *(ptr++) = (T)val;
      }
      if (err!=1)
        cimg::warn(_cimg_instance
                   "STR",
                   cimg_instance,
                   off - 1,siz,filename?filename:"STR");

      if (!file) cimg::fclose(nfile);
      return *this;
    }