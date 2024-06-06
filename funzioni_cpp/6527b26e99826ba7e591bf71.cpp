dissect_kafka_offset_fetch_response_partition(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree,
                                              int start_offset, kafka_api_version_t api_version)
{
    proto_item *ti;
    proto_tree *subtree;
    int         offset = start_offset;
    kafka_packet_values_t packet_values;
    memset(&packet_values, 0, sizeof(packet_values));

    subtree = proto_tree_add_subtree(tree, tvb, offset, -1, ett_kafka_partition, &ti, "STR");

    offset = dissect_kafka_partition_id_ret(tvb, pinfo, subtree, offset, &packet_values.partition_id);
    offset = dissect_kafka_offset_ret(tvb, pinfo, subtree, offset, &packet_values.offset);

    if (api_version >= 5) {
        offset = dissect_kafka_leader_epoch(tvb, pinfo, subtree, offset, api_version);
    }


    offset = dissect_kafka_string(subtree, hf_kafka_metadata, tvb, pinfo, offset, api_version >= 6, NULL, NULL);

    offset = dissect_kafka_error(tvb, pinfo, subtree, offset);

    if (packet_values.offset==-1) {
        proto_item_append_text(ti, "STR",
                               packet_values.partition_id);
    } else {
        proto_item_append_text(ti, "STR",
                               packet_values.partition_id, packet_values.offset);
    }

    if (api_version >= 6) {
        offset = dissect_kafka_tagged_fields(tvb, pinfo, subtree, offset, 0);
    }

    proto_item_set_end(ti, tvb, offset);

    return offset;
}