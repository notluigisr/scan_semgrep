static GF_Err gf_m4v_parse_frame_mpeg4(GF_M4VParser *m4v, GF_M4VDecSpecInfo dsi, u8 *frame_type, u32 *time_inc, u64 *size, u64 *start, Bool *is_coded)
{
	u8 go, hasVOP, firstObj, secs;
	s32 o_type;
	u32 vop_inc = 0;

	if (!m4v || !size || !start || !frame_type) return GF_BAD_PARAM;

	*size = 0;
	firstObj = 1;
	hasVOP = 0;
	*is_coded = 0;
	m4v->current_object_type = (u32) -1;
	*frame_type = 0;

	M4V_Reset(m4v, m4v->current_object_start);
	go = 1;
	while (go) {
		o_type = M4V_LoadObject(m4v);
		switch (o_type) {
		case M4V_VOP_START_CODE:
			
			if (hasVOP) {
				go = 0;
				break;
			}
			if (firstObj) {
				*start = m4v->current_object_start;
				firstObj = 0;
			}
			hasVOP = 1;

			
			*frame_type = gf_bs_read_int(m4v->bs, 2);
			
			secs = 0;
			while (gf_bs_read_int(m4v->bs, 1) != 0)
				secs ++;
			
			secs += (dsi.enh_layer || *frame_type!=2) ? m4v->tc_dec : m4v->tc_disp;
			
			gf_bs_read_int(m4v->bs, 1);
			
			if (dsi.NumBitsTimeIncrement)
				vop_inc = gf_bs_read_int(m4v->bs, dsi.NumBitsTimeIncrement);

			m4v->prev_tc_dec = m4v->tc_dec;
			m4v->prev_tc_disp = m4v->tc_disp;
			if (dsi.enh_layer || *frame_type!=2) {
				m4v->tc_disp = m4v->tc_dec;
				m4v->tc_dec = secs;
			}
			*time_inc = secs * dsi.clock_rate + vop_inc;
			
			gf_bs_read_int(m4v->bs, 1);
			
			*is_coded = gf_bs_read_int(m4v->bs, 1);
			gf_bs_align(m4v->bs);
			break;
		case M4V_GOV_START_CODE:
			if (firstObj) {
				*start = m4v->current_object_start;
				firstObj = 0;
			}
			if (hasVOP) go = 0;
			break;

		case M4V_VOS_START_CODE:
		case M4V_VOL_START_CODE:
			if (hasVOP) {
				go = 0;
			} else if (firstObj) {
				*start = m4v->current_object_start;
				firstObj = 0;
			}
			break;

		case M4V_VO_START_CODE:
		default:
			break;

		case -1:
			*size = gf_bs_get_position(m4v->bs) - *start;
			return GF_EOS;
		}
	}
	*size = m4v->current_object_start - *start;
	return GF_OK;
}