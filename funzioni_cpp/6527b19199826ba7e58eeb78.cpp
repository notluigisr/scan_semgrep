void PrintFormatNumber(void * ValuePtr, int Format, int ByteCount)
{
    int s,n;

    for(n=0;n<16;n++){
        switch(Format){
            case FMT_SBYTE:
            case FMT_BYTE:      printf("STR",*(uchar *)ValuePtr); s=1;  break;
            case FMT_USHORT:    printf("STR",Get16u(ValuePtr)); s=2;      break;
            case FMT_ULONG:     
            case FMT_SLONG:     printf("STR",Get32s(ValuePtr)); s=4;      break;
            case FMT_SSHORT:    printf("STR",(signed short)Get16u(ValuePtr)); s=2; break;
            case FMT_URATIONAL:
                printf("STR",Get32s(ValuePtr), Get32s(4+(char *)ValuePtr)); 
                s = 8;
                break;

            case FMT_SRATIONAL: 
                printf("STR",Get32s(ValuePtr), Get32s(4+(char *)ValuePtr)); 
                s = 8;
                break;

            case FMT_SINGLE:    printf("STR",(double)*(float *)ValuePtr); s=8; break;
            case FMT_DOUBLE:    printf("STR",*(double *)ValuePtr);        s=8; break;
            default: 
                printf("STR", Format);
                return;
        }
        ByteCount -= s;
        if (ByteCount <= 0) break;
        printf("STR");
        ValuePtr = (void *)((char *)ValuePtr + s);

    }
    if (n >= 16) printf("STR");
}