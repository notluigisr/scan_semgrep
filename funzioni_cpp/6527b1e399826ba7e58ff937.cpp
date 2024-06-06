MagickExport Image *GetImageMask(const Image *image,const PixelMask type,
  ExceptionInfo *exception)
{
  CacheView
    *mask_view,
    *image_view;

  Image
    *mask_image;

  MagickBooleanType
    status;

  ssize_t
    y;

  
  assert(image != (Image *) NULL);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"STR");
  assert(image->signature == MagickCoreSignature);
  mask_image=CloneImage(image,image->columns,image->rows,MagickTrue,exception);
  if (mask_image == (Image *) NULL)
    return((Image *) NULL);
  status=MagickTrue;
  mask_image->alpha_trait=UndefinedPixelTrait;
  (void) SetImageColorspace(mask_image,GRAYColorspace,exception);
  mask_image->read_mask=MagickFalse;
  image_view=AcquireVirtualCacheView(image,exception);
  mask_view=AcquireAuthenticCacheView(mask_image,exception);
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    register const Quantum
      *magick_restrict p;

    register Quantum
      *magick_restrict q;

    register ssize_t
      x;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,image->columns,1,exception);
    q=GetCacheViewAuthenticPixels(mask_view,0,y,mask_image->columns,1,
      exception);
    if ((p == (const Quantum *) NULL) || (q == (Quantum *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      switch (type)
      {
        case WritePixelMask:
        {
          SetPixelGray(mask_image,GetPixelWriteMask(image,p),q);
          break;
        }
        default:
        {
          SetPixelGray(mask_image,GetPixelReadMask(image,p),q);
          break;
        }
      }
      p+=GetPixelChannels(image);
      q+=GetPixelChannels(mask_image);
    }
    if (SyncCacheViewAuthenticPixels(mask_view,exception) == MagickFalse)
      status=MagickFalse;
  }
  mask_view=DestroyCacheView(mask_view);
  image_view=DestroyCacheView(image_view);
  if (status == MagickFalse)
    mask_image=DestroyImage(mask_image);
  return(mask_image);
}