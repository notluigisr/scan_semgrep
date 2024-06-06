static void __init mp_override_legacy_irq(u8 bus_irq, u8 polarity, u8 trigger,
					  u32 gsi)
{
	int ioapic;
	int pin;
	struct mpc_intsrc mp_irq;

	
	ioapic = mp_find_ioapic(gsi);
	if (ioapic < 0)
		return;
	pin = mp_find_ioapic_pin(ioapic, gsi);

	
	if ((bus_irq == 0) && (trigger == 3))
		trigger = 1;

	mp_irq.type = MP_INTSRC;
	mp_irq.irqtype = mp_INT;
	mp_irq.irqflag = (trigger << 2) | polarity;
	mp_irq.srcbus = MP_ISA_BUS;
	mp_irq.srcbusirq = bus_irq;	
	mp_irq.dstapic = mpc_ioapic_id(ioapic); 
	mp_irq.dstirq = pin;	

	mp_save_irq(&mp_irq);

	
	if (gsi < nr_legacy_irqs() && isa_irq_to_gsi[gsi] == gsi)
		isa_irq_to_gsi[gsi] = ACPI_INVALID_GSI;
	isa_irq_to_gsi[bus_irq] = gsi;
}