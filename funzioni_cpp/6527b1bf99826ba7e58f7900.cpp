_outRangeTblRef(StringInfo str, const RangeTblRef *node)
{
	WRITE_NODE_TYPE("STR");

	WRITE_INT_FIELD(rtindex);
}