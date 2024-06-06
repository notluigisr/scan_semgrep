Pl_LZWDecoder::getFirstChar(int code)
{
    unsigned char result = '\0';
    if (code < 256)
    {
	result = static_cast<unsigned char>(code);
    }
    else if (code > 257)
    {
	unsigned int idx = code - 258;
	if (idx >= table.size())
        {
            throw std::logic_error(
                "STR");
        }
	Buffer& b = table.at(idx);
	result = b.getBuffer()[0];
    }
    else
    {
        throw std::logic_error(
            "STR" +
            QUtil::int_to_string(code) + "STR");
    }
    return result;
}