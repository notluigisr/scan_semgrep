void buildMessage(SSL& ssl, output_buffer& output, const Message& msg)
{
    uint digestSz = ssl.getCrypto().get_digest().get_digestSize();
    uint sz  = RECORD_HEADER + msg.get_length() + digestSz;                
    uint pad = 0;
    uint blockSz = ssl.getCrypto().get_cipher().get_blockSize();

    if (ssl.getSecurity().get_parms().cipher_type_ == block) {
        if (ssl.isTLSv1_1())  
            sz += blockSz;
        sz += 1;       
        pad = (sz - RECORD_HEADER) % blockSz;
        pad = blockSz - pad;
        sz += pad;
    }

    RecordLayerHeader rlHeader;
    buildHeader(ssl, rlHeader, msg);
    rlHeader.length_ = sz - RECORD_HEADER;   
                                             
    input_buffer iv;
    if (ssl.isTLSv1_1() && ssl.getSecurity().get_parms().cipher_type_== block){
        iv.allocate(blockSz);
        ssl.getCrypto().get_random().Fill(iv.get_buffer(), blockSz);
        iv.add_size(blockSz);
    }
    
    uint ivSz = iv.get_size();
    output.allocate(sz);
    output << rlHeader << iv << msg;
    
    opaque digest[SHA_LEN];                  
    if (ssl.isTLS())
        TLS_hmac(ssl, digest, output.get_buffer() + RECORD_HEADER + ivSz,
                 output.get_size() - RECORD_HEADER - ivSz, msg.get_type());
    else
        hmac(ssl, digest, output.get_buffer() + RECORD_HEADER,
             output.get_size() - RECORD_HEADER, msg.get_type());
    output.write(digest, digestSz);

    if (ssl.getSecurity().get_parms().cipher_type_ == block)
        for (uint i = 0; i <= pad; i++) output[AUTO] = pad; 
                                                              
    input_buffer cipher(rlHeader.length_);
    ssl.useCrypto().use_cipher().encrypt(cipher.get_buffer(),
       output.get_buffer() + RECORD_HEADER, output.get_size() - RECORD_HEADER);
    output.set_current(RECORD_HEADER);
    output.write(cipher.get_buffer(), cipher.get_capacity());
}