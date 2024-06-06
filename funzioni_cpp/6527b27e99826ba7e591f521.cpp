encode_DELETE_FIELD(const struct ofpact_delete_field *delete_field,
                    enum ofp_version ofp_version OVS_UNUSED,
                    struct ofpbuf *out)
{
    struct nx_action_delete_field *nadf = put_NXAST_DELETE_FIELD(out);
    size_t size = out->size;

    out->size = size - sizeof nadf->pad;
    nx_put_mff_header(out, delete_field->field, 0, false);
    out->size = size;
}