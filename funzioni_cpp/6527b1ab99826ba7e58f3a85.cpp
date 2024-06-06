static int em_lgdt(struct x86_emulate_ctxt *ctxt)
{
	struct desc_ptr desc_ptr;
	int rc;

	rc = read_descriptor(ctxt, ctxt->src.addr.mem,
			     &desc_ptr.size, &desc_ptr.address,
			     ctxt->op_bytes);
	if (rc != X86EMUL_CONTINUE)
		return rc;
	ctxt->ops->set_gdt(ctxt, &desc_ptr);
	
	ctxt->dst.type = OP_NONE;
	return X86EMUL_CONTINUE;
}