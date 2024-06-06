static int csnmp_config_add_host_collect(host_definition_t *host,
                                         oconfig_item_t *ci) {
  data_definition_t *data;
  data_definition_t **data_list;
  int data_list_len;

  if (ci->values_num < 1) {
    WARNING("STR");
    return (-1);
  }

  for (int i = 0; i < ci->values_num; i++)
    if (ci->values[i].type != OCONFIG_TYPE_STRING) {
      WARNING("STR");
      return (-1);
    }

  data_list_len = host->data_list_len + ci->values_num;
  data_list =
      realloc(host->data_list, sizeof(data_definition_t *) * data_list_len);
  if (data_list == NULL)
    return (-1);
  host->data_list = data_list;

  for (int i = 0; i < ci->values_num; i++) {
    for (data = data_head; data != NULL; data = data->next)
      if (strcasecmp(ci->values[i].value.string, data->name) == 0)
        break;

    if (data == NULL) {
      WARNING("STR",
              ci->values[i].value.string);
      continue;
    }

    DEBUG("STR", host->name,
          host->data_list_len, data->name);

    host->data_list[host->data_list_len] = data;
    host->data_list_len++;
  } 

  return (0);
} 