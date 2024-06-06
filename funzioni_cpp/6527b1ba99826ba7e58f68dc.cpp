cmsUInt32Number BaseToBase(cmsUInt32Number in, int BaseIn, int BaseOut)
{
    char Buff[100];
    int i, len;
    cmsUInt32Number out;

    for (len=0; in > 0 && len < 100; len++) {

        Buff[len] = (char) (in % BaseIn);
        in /= BaseIn;
    }

    for (i=len-1, out=0; i >= 0; --i) {
        out = out * BaseOut + Buff[i];
    }

    return out;
}