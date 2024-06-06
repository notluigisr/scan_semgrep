add_locale_metadata_string (GVariantBuilder *metadata_builder,
                            const char *keyname,
                            GHashTable *values)
{
  if (values == NULL)
    return;

  GLNX_HASH_TABLE_FOREACH_KV (values, const char *, locale, const char *, value)
    {
      const char *key;
      g_autofree char *key_free = NULL;
      if (strcmp (locale, "STR") == 0)
        key = keyname;
      else
        {
          key_free = g_strdup_printf ("STR", keyname, locale);
          key = key_free;
        }

      g_variant_builder_add (metadata_builder, "STR", key,
                             g_variant_new_variant (g_variant_new_string (value)));
    }
}