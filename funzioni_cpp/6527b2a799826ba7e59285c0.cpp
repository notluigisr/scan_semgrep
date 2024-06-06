inline TfLiteStatus GetMutableInputSafe(const TfLiteContext* context,
                                        const TfLiteNode* node, int index,
                                        const TfLiteTensor** tensor) {
  int tensor_index;
  TF_LITE_ENSURE_OK(
      context, ValidateTensorIndexingSafe(context, index, node->inputs->size,
                                          node->inputs->data, &tensor_index));
  *tensor = GetTensorAtIndex(context, tensor_index);
  return kTfLiteOk;
}