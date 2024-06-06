INST_HANDLER (eijmp) {	
	ut64 z, eind;
	
	r_anal_esil_reg_read (anal->esil, "STR",    &z,    NULL);
	r_anal_esil_reg_read (anal->esil, "STR", &eind, NULL);
	
	
	op->jump = ((eind << 16) + z) << 1;
	
	ESIL_A ("STR");
	
	op->cycles = 2;
}