if (indir_needs_resize) {
  // Use ck_realloc to preserve existing coverage data
  // instead of ck_free + ck_alloc
  u32 old_indir_size = afl->shm.indir_map_size;
  afl->shm.indir_map_size = new_indir_map_size;
  afl->indir_virgin_bits =
      ck_realloc(afl->indir_virgin_bits, new_indir_map_size);
  afl->indir_virgin_tmout =
      ck_realloc(afl->indir_virgin_tmout, new_indir_map_size);
  afl->indir_virgin_crash =
      ck_realloc(afl->indir_virgin_crash, new_indir_map_size);
  afl->indir_top_rated =
      ck_realloc(afl->indir_top_rated,
                 new_indir_map_size * 8 * sizeof(struct queue_entry *));
  afl->indir_top_rated_candidates = ck_realloc(
      afl->indir_top_rated_candidates, new_indir_map_size * 8 * sizeof(u32 *));
  if (new_indir_map_size > old_indir_size) {
    memset(afl->indir_virgin_bits + old_indir_size, 255,
           new_indir_map_size - old_indir_size);
    memset(afl->indir_virgin_tmout + old_indir_size, 255,
           new_indir_map_size - old_indir_size);
    memset(afl->indir_virgin_crash + old_indir_size, 255,
           new_indir_map_size - old_indir_size);
    memset(afl->indir_top_rated + old_indir_size * 8, 0,
           (new_indir_map_size - old_indir_size) * 8 *
               sizeof(struct queue_entry *));
    memset(afl->indir_top_rated_candidates + old_indir_size * 8, 0,
           (new_indir_map_size - old_indir_size) * 8 * sizeof(u32 *));
    // Resize trace_mini_indir for all queued items to prevent
    // out-of-bounds in cull_queue
    for (u32 i = 0; i < afl->queued_items; i++) {
      struct queue_entry *q = afl->queue_buf[i];
      if (q && q->trace_mini_indir) {
        q->trace_mini_indir =
            ck_realloc(q->trace_mini_indir, new_indir_map_size);
        memset(q->trace_mini_indir + old_indir_size, 0,
               new_indir_map_size - old_indir_size);
      }
    }
  }
}