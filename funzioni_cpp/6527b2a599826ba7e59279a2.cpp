uint32_t riff_next_chunk(wav_reader_t *reader, uint32_t *chunk_size)
{
    uint32_t fcc;
    return (pcm_scanl(&reader->io, "STR", &fcc, chunk_size) == 2) ? fcc : 0;
}