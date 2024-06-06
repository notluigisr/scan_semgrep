static int _hostfs_release(oe_device_t* device)
{
    int ret = -1;
    device_t* fs = _cast_device(device);

    if (!fs)
        OE_RAISE_ERRNO(OE_EINVAL);

    oe_free(fs);
    ret = 0;

done:
    return ret;
}