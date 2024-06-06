GF_Err tims_dump(GF_Box *a, FILE * trace)
{
	GF_TSHintEntryBox *p;
	p = (GF_TSHintEntryBox *)a;
	gf_isom_box_dump_start(a, "STR", trace);
	fprintf(trace, "STR", p->timeScale);
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}