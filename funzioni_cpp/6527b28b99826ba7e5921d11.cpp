static int handle_fastpath_set_x2apic_icr_irqoff(struct kvm_vcpu *vcpu, u64 data)
{
	if (!lapic_in_kernel(vcpu) || !apic_x2apic_mode(vcpu->arch.apic))
		return 1;

	if (((data & APIC_SHORT_MASK) == APIC_DEST_NOSHORT) &&
	    ((data & APIC_DEST_MASK) == APIC_DEST_PHYSICAL) &&
	    ((data & APIC_MODE_MASK) == APIC_DM_FIXED) &&
	    ((u32)(data >> 32) != X2APIC_BROADCAST))
		return kvm_x2apic_icr_write(vcpu->arch.apic, data);

	return 1;
}