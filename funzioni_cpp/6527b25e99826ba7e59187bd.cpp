netsnmp_unload_module(const char *name)
{
    struct module  *mp;
    int             modID = -1;

    for (mp = module_head; mp; mp = mp->next)
        if (!label_compare(mp->name, name)) {
            modID = mp->modid;
            break;
        }

    if (modID == -1) {
        DEBUGMSGTL(("STR",
                    name));
        return MODULE_NOT_FOUND;
    }
    unload_module_by_ID(modID, tree_head);
    mp->no_imports = -1;        
    return MODULE_LOADED_OK;    
}