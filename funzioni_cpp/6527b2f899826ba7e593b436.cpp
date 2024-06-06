longlong Item_func_is_free_lock::val_int()
{
  DBUG_ASSERT(fixed == 1);
  String *res= args[0]->val_str(&value);
  THD *thd= current_thd;
  null_value= 1;

  if (!ull_name_ok(res))
    return 0;

  MDL_key ull_key;
  ull_key.mdl_key_init(MDL_key::USER_LOCK, res->c_ptr_safe(), "");

  null_value= 0;
  return thd->mdl_context.get_lock_owner(&ull_key) == 0;
}