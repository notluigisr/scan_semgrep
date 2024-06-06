static void iommu_enable_dev_iotlb(struct device_domain_info *info)
{
	struct pci_dev *pdev;

	assert_spin_locked(&device_domain_lock);

	if (!info || !dev_is_pci(info->dev))
		return;

	pdev = to_pci_dev(info->dev);
	
	if (!ecap_dit(info->iommu->ecap))
		info->pfsid = 0;
	else {
		struct pci_dev *pf_pdev;

		
		pf_pdev = pci_physfn(pdev);
		info->pfsid = PCI_DEVID(pf_pdev->bus->number, pf_pdev->devfn);
	}

#ifdef CONFIG_INTEL_IOMMU_SVM
	
	if (info->pasid_supported && !pci_enable_pasid(pdev, info->pasid_supported & ~1))
		info->pasid_enabled = 1;

	if (info->pri_supported && !pci_reset_pri(pdev) && !pci_enable_pri(pdev, 32))
		info->pri_enabled = 1;
#endif
	if (info->ats_supported && !pci_enable_ats(pdev, VTD_PAGE_SHIFT)) {
		info->ats_enabled = 1;
		domain_update_iotlb(info->domain);
		info->ats_qdep = pci_ats_queue_depth(pdev);
	}
}