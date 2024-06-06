QPDFWriter::write()
{
    doWriteSetup();

    
    
    
    
    
    
    this->m->events_expected = (
        this->m->pdf.getObjectCount() * (this->m->linearized ? 3 : 2));

    prepareFileForWrite();

    if (this->m->linearized)
    {
	writeLinearized();
    }
    else
    {
	writeStandard();
    }

    this->m->pipeline->finish();
    if (this->m->close_file)
    {
	fclose(this->m->file);
    }
    this->m->file = 0;
    if (this->m->buffer_pipeline)
    {
	this->m->output_buffer = this->m->buffer_pipeline->getBuffer();
	this->m->buffer_pipeline = 0;
    }
    indicateProgress(false, true);
}