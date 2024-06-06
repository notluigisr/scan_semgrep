prime_root(struct module_qstate* qstate, struct iter_qstate* iq, int id,
	uint16_t qclass)
{
	struct delegpt* dp;
	struct module_qstate* subq;
	verbose(VERB_DETAIL, "STR", 
		sldns_lookup_by_id(sldns_rr_classes, (int)qclass)?
		sldns_lookup_by_id(sldns_rr_classes, (int)qclass)->name:"STR");
	dp = hints_lookup_root(qstate->env->hints, qclass);
	if(!dp) {
		verbose(VERB_ALGO, "STR");
		return 0;
	}
	
	if(!generate_sub_request((uint8_t*)"STR", 1, LDNS_RR_TYPE_NS, 
		qclass, qstate, id, iq, QUERYTARGETS_STATE, PRIME_RESP_STATE,
		&subq, 0, 0)) {
		verbose(VERB_ALGO, "STR");
		return 0;
	}
	if(subq) {
		struct iter_qstate* subiq = 
			(struct iter_qstate*)subq->minfo[id];
		
		subiq->dp = delegpt_copy(dp, subq->region);
		if(!subiq->dp) {
			log_err("STR");
			fptr_ok(fptr_whitelist_modenv_kill_sub(
				qstate->env->kill_sub));
			(*qstate->env->kill_sub)(subq);
			return 0;
		}
		
		subiq->num_target_queries = 0; 
		subiq->dnssec_expected = iter_indicates_dnssec(
			qstate->env, subiq->dp, NULL, subq->qinfo.qclass);
	}
	
	
	qstate->ext_state[id] = module_wait_subquery;
	return 1;
}