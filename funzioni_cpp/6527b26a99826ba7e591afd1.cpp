static void __init resiliency_test(void)
{
	u8 *p;
	int type = KMALLOC_NORMAL;

	BUILD_BUG_ON(KMALLOC_MIN_SIZE > 16 || KMALLOC_SHIFT_HIGH < 10);

	pr_err("STR");
	pr_err("STR");
	pr_err("STR");

	p = kzalloc(16, GFP_KERNEL);
	p[16] = 0x12;
	pr_err("STR",
	       p + 16);

	validate_slab_cache(kmalloc_caches[type][4]);

	
	p = kzalloc(32, GFP_KERNEL);
	p[32 + sizeof(void *)] = 0x34;
	pr_err("STR",
	       p);
	pr_err("STR");

	validate_slab_cache(kmalloc_caches[type][5]);
	p = kzalloc(64, GFP_KERNEL);
	p += 64 + (get_cycles() & 0xff) * sizeof(void *);
	*p = 0x56;
	pr_err("STR",
	       p);
	pr_err("STR");
	validate_slab_cache(kmalloc_caches[type][6]);

	pr_err("STR");
	p = kzalloc(128, GFP_KERNEL);
	kfree(p);
	*p = 0x78;
	pr_err("STR", p);
	validate_slab_cache(kmalloc_caches[type][7]);

	p = kzalloc(256, GFP_KERNEL);
	kfree(p);
	p[50] = 0x9a;
	pr_err("STR", p);
	validate_slab_cache(kmalloc_caches[type][8]);

	p = kzalloc(512, GFP_KERNEL);
	kfree(p);
	p[512] = 0xab;
	pr_err("STR", p);
	validate_slab_cache(kmalloc_caches[type][9]);
}