static inline int audit_del_rule(struct audit_entry *entry,
				 struct list_head *list)
{
	struct audit_entry  *e;
	struct audit_field *inode_f = entry->rule.inode_f;
	struct audit_watch *watch, *tmp_watch = entry->rule.watch;
	struct audit_tree *tree = entry->rule.tree;
	LIST_HEAD(inotify_list);
	int h, ret = 0;
#ifdef CONFIG_AUDITSYSCALL
	int dont_count = 0;

	
	if (entry->rule.listnr == AUDIT_FILTER_USER ||
		entry->rule.listnr == AUDIT_FILTER_TYPE)
		dont_count = 1;
#endif

	if (inode_f) {
		h = audit_hash_ino(inode_f->val);
		list = &audit_inode_hash[h];
	}

	mutex_lock(&audit_filter_mutex);
	e = audit_find_rule(entry, list);
	if (!e) {
		mutex_unlock(&audit_filter_mutex);
		ret = -ENOENT;
		goto out;
	}

	watch = e->rule.watch;
	if (watch) {
		struct audit_parent *parent = watch->parent;

		list_del(&e->rule.rlist);

		if (list_empty(&watch->rules)) {
			audit_remove_watch(watch);

			if (list_empty(&parent->watches)) {
				
				list_add(&parent->ilist, &inotify_list);
				get_inotify_watch(&parent->wdata);
			}
		}
	}

	if (e->rule.tree)
		audit_remove_tree_rule(&e->rule);

	list_del_rcu(&e->list);
	call_rcu(&e->rcu, audit_free_rule_rcu);

#ifdef CONFIG_AUDITSYSCALL
	if (!dont_count)
		audit_n_rules--;

	if (!audit_match_signal(entry))
		audit_signals--;
#endif
	mutex_unlock(&audit_filter_mutex);

	if (!list_empty(&inotify_list))
		audit_inotify_unregister(&inotify_list);

out:
	if (tmp_watch)
		audit_put_watch(tmp_watch); 
	if (tree)
		audit_put_tree(tree);	

	return ret;
}