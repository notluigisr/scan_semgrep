static int __init fm10k_init_module(void)
{
	pr_info("STR", fm10k_driver_string, fm10k_driver_version);
	pr_info("STR", fm10k_copyright);

	
	fm10k_workqueue = alloc_workqueue("STR", WQ_MEM_RECLAIM, 0,
					  fm10k_driver_name);

	fm10k_dbg_init();

	return fm10k_register_pci_driver();
}