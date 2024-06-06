bytesPerDeepLineTable (const Header &header,
                       int minY, int maxY,
                       const char* base,
                       int xStride,
                       int yStride,
                       vector<size_t> &bytesPerLine)
{
    const Box2i &dataWindow = header.dataWindow();
    const ChannelList &channels = header.channels();

    for (ChannelList::ConstIterator c = channels.begin();
         c != channels.end();
         ++c)
    {
        const int ySampling = abs(c.channel().ySampling);
        const int xSampling = abs(c.channel().xSampling);
        const int pixelSize = pixelTypeSize (c.channel().type);

        
        
        
        
        
        
        
        
        const int sampleMinY = roundToNextMultiple(minY, ySampling);
        const int sampleMaxY = roundToPrevMultiple(maxY, ySampling);
        const int sampleMinX = roundToNextMultiple(dataWindow.min.x, xSampling);
        const int sampleMaxX = roundToPrevMultiple(dataWindow.max.x, xSampling);

        for (int y = sampleMinY; y <= sampleMaxY; y+=ySampling)
        {
            int nBytes = 0;
            for (int x = sampleMinX; x <= sampleMaxX; x += xSampling)
            {
                nBytes += pixelSize *
                          sampleCount(base, xStride, yStride, x, y);
            }
            bytesPerLine[y - dataWindow.min.y] += nBytes;
        }
    }

    size_t maxBytesPerLine = 0;

    for (int y = minY; y <= maxY; ++y)
        if (maxBytesPerLine < bytesPerLine[y - dataWindow.min.y])
            maxBytesPerLine = bytesPerLine[y - dataWindow.min.y];

    return maxBytesPerLine;
}