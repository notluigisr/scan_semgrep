void HGraphBuilder::HandleLiteralCompareNil(CompareOperation* expr,
                                            HValue* value,
                                            NilValue nil) {
  ASSERT(!HasStackOverflow());
  ASSERT(current_block() != NULL);
  ASSERT(current_block()->HasPredecessor());
  EqualityKind kind =
      expr->op() == Token::EQ_STRICT ? kStrictEquality : kNonStrictEquality;
  HIsNilAndBranch* instr = new(zone()) HIsNilAndBranch(value, kind, nil);
  instr->set_position(expr->position());
  return ast_context()->ReturnControl(instr, expr->id());
}