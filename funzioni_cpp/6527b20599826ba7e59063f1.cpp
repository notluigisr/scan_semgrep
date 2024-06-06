int ha_partition::set_up_table_before_create(TABLE *tbl,
                    const char *partition_name_with_path, 
                    HA_CREATE_INFO *info,
                    uint part_id,
                    partition_element *part_elem)
{
  int error= 0;
  const char *partition_name;
  THD *thd= ha_thd();
  DBUG_ENTER("STR");

  if (!part_elem)
  {
    part_elem= find_partition_element(part_id);
    if (!part_elem)
      DBUG_RETURN(1);                             
  }
  tbl->s->max_rows= part_elem->part_max_rows;
  tbl->s->min_rows= part_elem->part_min_rows;
  partition_name= strrchr(partition_name_with_path, FN_LIBCHAR);
  if ((part_elem->index_file_name &&
      (error= append_file_to_dir(thd,
                                 (const char**)&part_elem->index_file_name,
                                 partition_name+1))) ||
      (part_elem->data_file_name &&
      (error= append_file_to_dir(thd,
                                 (const char**)&part_elem->data_file_name,
                                 partition_name+1))))
  {
    DBUG_RETURN(error);
  }
  info->index_file_name= part_elem->index_file_name;
  info->data_file_name= part_elem->data_file_name;
  DBUG_RETURN(0);
}