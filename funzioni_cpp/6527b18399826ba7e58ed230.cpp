static Image *ReadVIDImage(const ImageInfo *image_info,ExceptionInfo *exception)
{


  char
    **filelist,
    *label,
    **list;

  Image
    *image,
    *images,
    *montage_image,
    *next_image,
    *thumbnail_image;

  ImageInfo
    *read_info;

  int
    number_files;

  MagickBooleanType
    status;

  MontageInfo
    *montage_info;

  RectangleInfo
    geometry;

  register ssize_t
    i;

  
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  if (image_info->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"STR",
      image_info->filename);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  image=AcquireImage(image_info);
  list=(char **) AcquireMagickMemory(sizeof(*filelist));
  if (list == (char **) NULL)
    ThrowReaderException(ResourceLimitError,"STR");
  list[0]=ConstantString(image_info->filename);
  filelist=list;
  number_files=1;
  status=ExpandFilenames(&number_files,&filelist);
  list[0]=DestroyString(list[0]);
  list=(char **) RelinquishMagickMemory(list);
  if ((status == MagickFalse) || (number_files == 0))
    ThrowReaderException(ResourceLimitError,"STR");
  image=DestroyImage(image);
  
  images=NewImageList();
  read_info=CloneImageInfo(image_info);
  SetImageInfoBlob(read_info,(void *) NULL,0);
  (void) SetImageInfoProgressMonitor(read_info,(MagickProgressMonitor) NULL,
    (void *) NULL);
  if (read_info->size == (char *) NULL)
    (void) CloneString(&read_info->size,DefaultTileGeometry);
  for (i=0; i < (ssize_t) number_files; i++)
  {
    if (image_info->debug != MagickFalse)
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),"STR",
        filelist[i]);
    (void) CopyMagickString(read_info->filename,filelist[i],MaxTextExtent);
    filelist[i]=DestroyString(filelist[i]);
    *read_info->magick='\0';
    next_image=ReadImage(read_info,exception);
    CatchException(exception);
    if (next_image == (Image *) NULL)
      break;
    label=InterpretImageProperties(image_info,next_image,DefaultTileLabel);
    (void) SetImageProperty(next_image,"STR",label);
    label=DestroyString(label);
    if (image_info->debug != MagickFalse)
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
        "STR",(double) next_image->columns,(double)
        next_image->rows);
    SetGeometry(next_image,&geometry);
    (void) ParseMetaGeometry(read_info->size,&geometry.x,&geometry.y,
      &geometry.width,&geometry.height);
    thumbnail_image=ThumbnailImage(next_image,geometry.width,geometry.height,
      exception);
    if (thumbnail_image != (Image *) NULL)
      {
        next_image=DestroyImage(next_image);
        next_image=thumbnail_image;
      }
    if (image_info->debug != MagickFalse)
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
        "STR",(double) next_image->columns,(double)
        next_image->rows);
    AppendImageToList(&images,next_image);
    status=SetImageProgress(images,LoadImagesTag,i,number_files);
    if (status == MagickFalse)
      break;
  }
  read_info=DestroyImageInfo(read_info);
  filelist=(char **) RelinquishMagickMemory(filelist);
  if (images == (Image *) NULL)
    ThrowReaderException(CorruptImageError,
      "STR");
  
  montage_info=CloneMontageInfo(image_info,(MontageInfo *) NULL);
  if (image_info->debug != MagickFalse)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),"STR");
  montage_image=MontageImageList(image_info,montage_info,
    GetFirstImageInList(images),exception);
  montage_info=DestroyMontageInfo(montage_info);
  images=DestroyImageList(images);
  return(montage_image);
}