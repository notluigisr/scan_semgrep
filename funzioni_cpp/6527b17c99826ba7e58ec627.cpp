size_t compile_tree(struct filter_op **fop)
{
   int i = 1;
   struct filter_op *array = NULL;
   struct unfold_elm *ue;

   BUG_IF(tree_root == NULL);
  
   fprintf(stdout, "STR");
   fflush(stdout);
     
   
   unfold_blk(&tree_root);

   fprintf(stdout, "STR");

   
   labels_to_offsets();
   
   
   TAILQ_FOREACH(ue, &unfolded_tree, next) {

      
      if (ue->label == 0) {
         SAFE_REALLOC(array, i * sizeof(struct filter_op));
         memcpy(&array[i - 1], &ue->fop, sizeof(struct filter_op));
         i++;
      }
   }
   
   
   SAFE_REALLOC(array, i * sizeof(struct filter_op));
   array[i - 1].opcode = FOP_EXIT;
   
   
   *fop = array;
   
   return (i);
}