int kvm_fix_hypercall(struct kvm_vcpu *vcpu)
{
	char instruction[3];
	int ret = 0;
	unsigned long rip = kvm_rip_read(vcpu);


	
	kvm_mmu_zap_all(vcpu->kvm);

	kvm_x86_ops->patch_hypercall(vcpu, instruction);
	if (emulator_write_emulated(rip, instruction, 3, vcpu)
	    != X86EMUL_CONTINUE)
		ret = -EFAULT;

	return ret;
}