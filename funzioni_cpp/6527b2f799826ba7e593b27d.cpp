bool Item_sum_bit::add_as_window(ulonglong value)
{
  DBUG_ASSERT(as_window_function);
  for (int i= 0; i < NUM_BIT_COUNTERS; i++)
  {
    bit_counters[i]+= (value & (1ULL << i)) ? 1 : 0;
  }
  
  num_values_added = MY_MAX(num_values_added, num_values_added + 1);
  set_bits_from_counters();
  return 0;
}