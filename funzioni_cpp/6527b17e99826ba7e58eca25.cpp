void CompressTest::testManipulator()
{
	{
		std::ofstream out("STR", std::ios::binary);
		Poco::Path theFile(ZipTest::getTestFile("STR"));
		Compress c(out, true);
		c.addFile(theFile, theFile.getFileName());
		ZipArchive a(c.close());
	}
	ZipManipulator zm("STR", true);
	zm.renameFile("STR");
	zm.addFile("STR"));
	ZipArchive archive=zm.commit();
	assert (archive.findHeader("STR") != archive.headerEnd());
}