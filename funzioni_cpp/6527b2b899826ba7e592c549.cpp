int pointZZ_pIsIdentityElement(const PointZZ_p * op) {
    return mpz_cmp_ui(op->x, 0) == 0 && mpz_cmp_ui(op->y, 0) == 0 ? 1 : 0;
}