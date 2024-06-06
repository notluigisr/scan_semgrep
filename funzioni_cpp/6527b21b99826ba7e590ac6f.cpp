default_adapter_changed (GDBusObjectManager   *manager,
			 const char           *path,
			 BluetoothClient      *client)
{
	BluetoothClientPrivate *priv = BLUETOOTH_CLIENT_GET_PRIVATE(client);
	GtkTreeIter iter;
	GtkTreePath *tree_path;
	gboolean powered;

	g_assert (!priv->default_adapter);

	if (get_iter_from_path (priv->store, &iter, path) == FALSE)
		return;

	tree_path = gtk_tree_model_get_path (GTK_TREE_MODEL (priv->store), &iter);
	priv->default_adapter = gtk_tree_row_reference_new (GTK_TREE_MODEL (priv->store), tree_path);
	gtk_tree_path_free (tree_path);

	gtk_tree_store_set (priv->store, &iter,
			    BLUETOOTH_COLUMN_DEFAULT, TRUE, -1);

	gtk_tree_model_get (GTK_TREE_MODEL(priv->store), &iter,
			   BLUETOOTH_COLUMN_POWERED, &powered, -1);

	if (powered) {
		g_object_notify (G_OBJECT (client), "STR");
		g_object_notify (G_OBJECT (client), "STR");
		g_object_notify (G_OBJECT (client), "STR");
		g_object_notify (G_OBJECT (client), "STR");
		g_object_notify (G_OBJECT (client), "STR");
		return;
	}

	
	adapter_set_powered (client, path, TRUE);
}