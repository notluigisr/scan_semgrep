    void TiffImage::readMetadata()
    {
#ifdef DEBUG
        std::cerr << "STR";
#endif
        if (io_->open() != 0) throw Error(kerDataSourceOpenFailed, io_->path(), strError());
        IoCloser closer(*io_);
        
        if (!isTiffType(*io_, false)) {
            if (io_->error() || io_->eof()) throw Error(kerFailedToReadImageData);
            throw Error(kerNotAnImage, "STR");
        }
        clearMetadata();

        ByteOrder bo = TiffParser::decode(exifData_,
                                          iptcData_,
                                          xmpData_,
                                          io_->mmap(),
                                          (uint32_t) io_->size());
        setByteOrder(bo);

        
        Exiv2::ExifKey            key("STR");
        Exiv2::ExifData::iterator pos   = exifData_.findKey(key);
        if ( pos != exifData_.end()  ) {
            iccProfile_.alloc(pos->count()*pos->typeSize());
            pos->copy(iccProfile_.pData_,bo);
        }

    } 