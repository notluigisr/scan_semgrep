
			gf_dynstrcat(&ds->rep->dasher_ctx->mux_pids, szMuxPID, NULL);
		}

	}
}

static GF_DashStream *dasher_get_stream(GF_DasherCtx *ctx, const char *src_url, u32 original_pid, u32 pid_id)
{
	u32 i, count = gf_list_count(ctx->pids);