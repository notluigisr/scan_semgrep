      static double mp_image_display(_cimg_math_parser& mp) {
        mp_check_list(mp,"STR");
        const unsigned int ind = (unsigned int)cimg::mod((int)_mp_arg(2),mp.imglist.width());
        cimg::mutex(6);
        CImg<T> &img = mp.imglist[ind];
        CImg<charT> title(256);
        std::fputc('\n',cimg::output());
        cimg_snprintf(title,title._width,"STR",ind);
        img.display(title);
        cimg::mutex(6,0);
        return cimg::type<double>::nan();
      }