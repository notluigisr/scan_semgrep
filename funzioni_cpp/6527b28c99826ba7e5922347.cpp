void LIRGenerator::volatile_field_load(LIR_Address* address, LIR_Opr result,
                                       CodeEmitInfo* info) {
  if (address->type() == T_LONG) {
    address = new LIR_Address(address->base(),
                              address->index(), address->scale(),
                              address->disp(), T_DOUBLE);
    
    
    
    
    LIR_Opr temp_double = new_register(T_DOUBLE);
    __ volatile_move(LIR_OprFact::address(address), temp_double, T_LONG, info);
    __ volatile_move(temp_double, result, T_LONG);
#ifndef _LP64
    if (UseSSE < 2) {
      
      set_vreg_flag(result, must_start_in_memory);
    }
#endif 
  } else {
    __ load(address, result, info);
  }
}