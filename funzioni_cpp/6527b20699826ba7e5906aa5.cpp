	string createErrorPageFromStderrOutput(const string &msg,
		SpawnException::ErrorKind errorKind,
		const string &stderrOutput)
	{
		
		assert(errorKind != SpawnException::PRELOADER_STARTUP_EXPLAINABLE_ERROR);
		assert(errorKind != SpawnException::APP_STARTUP_EXPLAINABLE_ERROR);

		string result = escapeHTML(msg);

		if (errorKind == SpawnException::PRELOADER_STARTUP_TIMEOUT
		 || errorKind == SpawnException::APP_STARTUP_TIMEOUT
		 || errorKind == SpawnException::PRELOADER_STARTUP_ERROR
		 || errorKind == SpawnException::APP_STARTUP_ERROR)
		{
			result.append("STR"
				"STR");
		}
		result.append("STR");

		if (strip(stderrOutput).empty()) {
			result.append("STR");
		} else {
			result.append("STR");
			result.append(escapeHTML(stderrOutput));
			result.append("STR");
		}

		return result;
	}