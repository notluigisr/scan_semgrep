static NTSTATUS dcesrv_lsa_Close(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
			  struct lsa_Close *r)
{
	enum dcerpc_transport_t transport =
		dcerpc_binding_get_transport(dce_call->conn->endpoint->ep_description);
	struct dcesrv_handle *h;

	if (transport != NCACN_NP && transport != NCALRPC) {
		DCESRV_FAULT(DCERPC_FAULT_ACCESS_DENIED);
	}

	*r->out.handle = *r->in.handle;

	DCESRV_PULL_HANDLE(h, r->in.handle, DCESRV_HANDLE_ANY);

	talloc_free(h);

	ZERO_STRUCTP(r->out.handle);

	return NT_STATUS_OK;
}