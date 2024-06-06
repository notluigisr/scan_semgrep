void Ogg::XiphComment::parse(const ByteVector &data)
{
  
  

  int pos = 0;

  int vendorLength = data.mid(0, 4).toUInt(false);
  pos += 4;

  d->vendorID = String(data.mid(pos, vendorLength), String::UTF8);
  pos += vendorLength;

  

  int commentFields = data.mid(pos, 4).toUInt(false);
  pos += 4;

  for(int i = 0; i < commentFields; i++) {

    
    

    int commentLength = data.mid(pos, 4).toUInt(false);
    pos += 4;

    String comment = String(data.mid(pos, commentLength), String::UTF8);
    pos += commentLength;

    int commentSeparatorPosition = comment.find("STR");

    String key = comment.substr(0, commentSeparatorPosition);
    String value = comment.substr(commentSeparatorPosition + 1);

    addField(key, value, false);
  }
}