static void sev_unlock_two_vms(struct kvm *dst_kvm, struct kvm *src_kvm)
{
	struct kvm_sev_info *dst_sev = &to_kvm_svm(dst_kvm)->sev_info;
	struct kvm_sev_info *src_sev = &to_kvm_svm(src_kvm)->sev_info;

	mutex_unlock(&dst_kvm->lock);
	mutex_unlock(&src_kvm->lock);
	atomic_set_release(&dst_sev->migration_in_progress, 0);
	atomic_set_release(&src_sev->migration_in_progress, 0);
}