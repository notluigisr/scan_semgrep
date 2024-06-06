ScanLineInputFile::ScanLineInputFile(InputPartData* part)
{
    if (part->header.type() != SCANLINEIMAGE)
        throw IEX_NAMESPACE::ArgExc("STR");

    _data = new Data(part->numThreads);
    _streamData = part->mutex;
    _data->memoryMapped = _streamData->is->isMemoryMapped();

    _data->version = part->version;

    initialize(part->header);

    _data->lineOffsets = part->chunkOffsets;

    _data->partNumber = part->partNumber;
    
    
    
    
    _data->fileIsComplete = true;
}