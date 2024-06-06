_vte_table_printi(struct _vte_table *table, const char *lead, int *count)
{
	unsigned int i;
	char *newlead = NULL;

	(*count)++;

	
	if (table->result != NULL) {
		g_printerr("STR", lead,
			table->result, table->increment);
	}

	
	for (i = 1; i < VTE_TABLE_MAX_LITERAL; i++) {
		if ((table->table != NULL) && (table->table[i] != NULL)) {
			if (i < 32) {
				newlead = g_strdup_printf("STR", lead,
							  i + 64);
			} else {
				newlead = g_strdup_printf("STR", lead, i);
			}
			_vte_table_printi(table->table[i], newlead, count);
			g_free(newlead);
		}
	}

	
	if (table->table_string != NULL) {
		newlead = g_strdup_printf("STR", lead);
		_vte_table_printi(table->table_string,
				  newlead, count);
		g_free(newlead);
	}

	
	if (table->table_number != NULL) {
		newlead = g_strdup_printf("STR", lead);
		_vte_table_printi(table->table_number,
				  newlead, count);
		g_free(newlead);
	}
}