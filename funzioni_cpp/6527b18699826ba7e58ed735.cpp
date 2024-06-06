DeepScanLineInputFile::~DeepScanLineInputFile ()
{
    if (_data->_deleteStream)
        delete _data->_streamData->is;

    if (_data)
    {
        if (!_data->memoryMapped)
            for (size_t i = 0; i < _data->lineBuffers.size(); i++)
                delete [] _data->lineBuffers[i]->buffer;

        
        
        
        
        
        
        
        
        
        

        if (_data->partNumber == -1 && _data->_streamData)
            delete _data->_streamData;

        delete _data;
    }
}