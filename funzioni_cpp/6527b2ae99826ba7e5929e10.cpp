GF_Err tfhd_box_dump(GF_Box *a, FILE * trace)
{
	GF_TrackFragmentHeaderBox *p;
	p = (GF_TrackFragmentHeaderBox *)a;
	gf_isom_box_dump_start(a, "STR", trace);
	gf_fprintf(trace, "STR", p->trackID);

	if (p->flags & GF_ISOM_TRAF_BASE_OFFSET) {
		gf_fprintf(trace, "STR", p->base_data_offset);
	} else {
		gf_fprintf(trace, "STR");
	}

	if (p->flags & GF_ISOM_TRAF_SAMPLE_DESC)
		gf_fprintf(trace, "STR", p->sample_desc_index);
	if (p->flags & GF_ISOM_TRAF_SAMPLE_DUR)
		gf_fprintf(trace, "STR", p->def_sample_duration);
	if (p->flags & GF_ISOM_TRAF_SAMPLE_SIZE)
		gf_fprintf(trace, "STR", p->def_sample_size);

	if (p->flags & GF_ISOM_TRAF_SAMPLE_FLAGS) {
		frag_dump_sample_flags(trace, p->def_sample_flags, 3);
	}

	gf_fprintf(trace, "STR");

	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}