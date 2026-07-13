void __afl_trace_indir(uint32_t *guard, uintptr_t target_addr) {
  if (unlikely(!__afl_indir_ptr || __afl_indir_ptr == __afl_indir_ptr_dummy))
    return;

  if (unlikely(!(*guard))) 
    return;

  indir_slot_t *indir_map_slots = (indir_slot_t *)__afl_indir_ptr;
  uint8_t bit_idx = (uint8_t)(((target_addr >> 4) * 0x9E3779B97F4A7C15ULL) >> (64 - INDIR_BIT_SHIFT));

  indir_map_slots[*guard] |= ((indir_slot_t)1 << bit_idx);
}