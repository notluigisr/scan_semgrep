static inline pte_t pte_mkexec(pte_t pte)
{
	return pte_clear_flags(pte, _PAGE_NX);
}