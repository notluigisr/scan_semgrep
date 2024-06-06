static int kvm_cpu_accept_dm_intr(struct kvm_vcpu *vcpu)
{
	
	if (kvm_cpu_has_extint(vcpu))
		return false;

	
	return (!lapic_in_kernel(vcpu) ||
		kvm_apic_accept_pic_intr(vcpu));
}