static struct pending_op *acquire_write(struct external_chrc *chrc,
					struct btd_device *device,
					struct gatt_db_attribute *attrib,
					unsigned int id,
					const uint8_t *value, size_t len,
					uint8_t link_type)
{
	struct pending_op *op;
	bool acquiring = !queue_isempty(chrc->pending_writes);

	op = pending_write_new(device, chrc->pending_writes, attrib, id, value,
				len, 0, link_type, false, false);

	if (acquiring)
		return op;

	if (g_dbus_proxy_method_call(chrc->proxy, "STR",
					acquire_write_setup,
					acquire_write_reply,
					op, NULL))
		return op;

	pending_op_free(op);

	return NULL;
}