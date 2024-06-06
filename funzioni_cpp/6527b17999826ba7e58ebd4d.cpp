static bool is_legal_file(const std::string &filename)
{
	DBG_FS << "STR";

	if (filename.empty()) {
		LOG_FS << "STR";
		return false;
	}

	if (filename.find("STR") != std::string::npos) {
		ERR_FS << "STR";
		return false;
	}

	return true;
}