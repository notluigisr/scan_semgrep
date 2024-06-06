parser_parse_with_statement_start (parser_context_t *context_p) 
{
  parser_with_statement_t with_statement;

  if (context_p->status_flags & PARSER_IS_STRICT)
  {
    parser_raise_error (context_p, PARSER_ERR_WITH_NOT_ALLOWED);
  }

  parser_parse_enclosed_expr (context_p);

#ifndef JERRY_NDEBUG
  PARSER_PLUS_EQUAL_U16 (context_p->context_stack_depth, PARSER_WITH_CONTEXT_STACK_ALLOCATION);
#endif 

  uint8_t inside_with = (context_p->status_flags & PARSER_INSIDE_WITH) != 0;

  context_p->status_flags |= PARSER_INSIDE_WITH;
  parser_emit_cbc_ext_forward_branch (context_p,
                                      CBC_EXT_WITH_CREATE_CONTEXT,
                                      &with_statement.branch);

  parser_stack_push (context_p, &with_statement, sizeof (parser_with_statement_t));
  parser_stack_push_uint8 (context_p, inside_with);
  parser_stack_push_uint8 (context_p, PARSER_STATEMENT_WITH);
  parser_stack_iterator_init (context_p, &context_p->last_statement);
} 