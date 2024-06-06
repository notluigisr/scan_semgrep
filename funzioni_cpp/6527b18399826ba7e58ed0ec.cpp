DnDCreateRootStagingDirectory(void)
{
   const char *root;

   
   root = DnD_GetFileRoot();
   if (!root) {
      return NULL;
   }

   if (File_Exists(root)) {
      if (!DnDRootDirUsable(root) &&
          !DnDSetPermissionsOnRootDir(root)) {
         
         return NULL;
      }
   } else {
      if (!File_CreateDirectory(root) ||
          !DnDSetPermissionsOnRootDir(root)) {
         
         return NULL;
      }
   }

   return root;
}