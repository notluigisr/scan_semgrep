mt_free(mrb_state *mrb, mt_tbl *t)
{
  mrb_free(mrb, t->ptr);
  mrb_free(mrb, t);
}