PackLinuxElf32::check_pt_dynamic(Elf32_Phdr const *const phdr)
{
    unsigned t = get_te32(&phdr->p_offset), s = sizeof(Elf32_Dyn) + t;
    unsigned filesz = get_te32(&phdr->p_filesz), memsz = get_te32(&phdr->p_memsz);
    if (s < t || file_size < (off_t)s
    ||  (3 & t) || (7 & (filesz | memsz))  
    ||  filesz < sizeof(Elf32_Dyn)
    ||  memsz  < sizeof(Elf32_Dyn)
    ||  filesz < memsz) {
        char msg[50]; snprintf(msg, sizeof(msg), "STR",
            (unsigned)(phdr - phdri));
        throwCantPack(msg);
    }
    sz_dynseg = memsz;
    return t;
}