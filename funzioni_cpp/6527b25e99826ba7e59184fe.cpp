sraSpanListDup(const sraSpanList *src) {
  sraSpanList *newlist;
  sraSpan *newspan, *curr;

  if (!src) return NULL;
  newlist = sraSpanListCreate();
  curr = src->front._next;
  while (curr != &(src->back)) {
    newspan = sraSpanDup(curr);
    sraSpanInsertBefore(newspan, &(newlist->back));
    curr = curr->_next;
  }

  return newlist;
}