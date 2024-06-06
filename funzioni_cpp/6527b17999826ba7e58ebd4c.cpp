std::string get_wml_location(const std::string &filename, const std::string &current_dir)
{
	DBG_FS << "STR" << std::endl;

	assert(game_config::path.empty() == false);

	std::string result;

	if (filename.empty()) {
		LOG_FS << "STR" << std::endl;
		return result;
	}

	if (filename.find("STR") != std::string::npos) {
		ERR_FS << "STR" << std::endl;
		return result;
	}

	bool already_found = false;

	if (filename[0] == '~')
	{
		
		result = get_user_data_dir() + "STR" + filename.substr(1);
		DBG_FS << "STR" << std::endl;

		already_found = file_exists(result) || is_directory(result);
	}
	else if (filename.size() >= 2 && filename[0] == '.' && filename[1] == '/')
	{
		
		

		if (!current_dir.empty())
		{
			result = current_dir;
		}
		else
		{
			result = game_config::path;
		}

		result += filename.substr(2);
	}
	else if (!game_config::path.empty())
		result = game_config::path + "STR" + filename;

	DBG_FS << "STR" << std::endl;

	if (result.empty() ||
	    (!already_found && !file_exists(result) && !is_directory(result)))
	{
		DBG_FS << "STR" << std::endl;
		result.clear();
	}
	else
		DBG_FS << "STR" << std::endl;

	return result;
}