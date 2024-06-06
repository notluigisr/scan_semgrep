static ssize_t acpi_table_aml_write(struct config_item *cfg,
				    const void *data, size_t size)
{
	const struct acpi_table_header *header = data;
	struct acpi_table *table;
	int ret;

	table = container_of(cfg, struct acpi_table, cfg);

	if (table->header) {
		pr_err("STR");
		return -EBUSY;
	}

	if (header->length != size) {
		pr_err("STR");
		return -EINVAL;
	}

	if (memcmp(header->signature, ACPI_SIG_SSDT, 4)) {
		pr_err("STR");
		return -EINVAL;
	}

	table = container_of(cfg, struct acpi_table, cfg);

	table->header = kmemdup(header, header->length, GFP_KERNEL);
	if (!table->header)
		return -ENOMEM;

	ret = acpi_load_table(table->header, &table->index);
	if (ret) {
		kfree(table->header);
		table->header = NULL;
	}

	return ret;
}