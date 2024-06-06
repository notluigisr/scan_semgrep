static struct db_arg_chain_tree *_db_node_get(struct db_arg_chain_tree *node)
{
	node->refcnt++;
	return node;
}