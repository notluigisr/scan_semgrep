  StringCrosser(const std::vector<
                    std::unique_ptr<ColumnInterface<InternalType>>>& columns,
                const int64 num_buckets_unused, const uint64 hash_key_unused,
                const tstring k_feature_separator)
      : columns_(columns), k_feature_separator_(k_feature_separator) {}