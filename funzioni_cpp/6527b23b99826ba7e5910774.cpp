      
      CImg<uintT> get_level(CImg<charT>& _expr) const {
        bool is_escaped = false, next_is_escaped = false;
        unsigned int mode = 0, next_mode = 0; 
        CImg<uintT> res(_expr._width - 1);
        unsigned int *pd = res._data;
        int _level = 0;
        for (const char *ps = _expr._data; *ps && _level>=0; ++ps) {
          if (!is_escaped && !next_is_escaped && *ps=='\\') next_is_escaped = true;
          if (!is_escaped && *ps=='\'') { 
            if (!mode && ps>_expr._data && *(ps - 1)=='[') next_mode = mode = 2; 
            else if (mode==2 && *(ps + 1)==']') next_mode = !mode; 
            else if (mode<2) next_mode = mode?(mode = 0):1; 
          }
          *(pd++) = (unsigned int)(mode>=1 || is_escaped?_level + (mode==1):
                                   *ps=='(' || *ps=='['?_level++:
                                   *ps==')' || *ps==']'?--_level:
                                   _level);
          mode = next_mode;
          is_escaped = next_is_escaped;
          next_is_escaped = false;
        }
        if (mode) {
          cimg::strellipsize(_expr,64);
          throw CImgArgumentException("STR"
                                      "STR",
                                      pixel_type(),_cimg_mp_calling_function,
                                      _expr._data);
        }
        if (_level) {
          cimg::strellipsize(_expr,64);
          throw CImgArgumentException("STR"
                                      "STR",
                                      pixel_type(),_cimg_mp_calling_function,
                                      _expr._data);
        }
        return res;