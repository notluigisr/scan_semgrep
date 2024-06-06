    
    static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4) {
      disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = false;
      while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed) &&
             !disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event) wait_all();