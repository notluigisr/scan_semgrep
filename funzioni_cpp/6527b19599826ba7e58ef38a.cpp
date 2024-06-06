void next_character(void)
{
    
    strlcpy(cipher, english_alphabet, ENGLISH_ALPHABET_BUF);
    random_permute_char(cipher, strlen(cipher));

    static char CONFIDENTIAL current_word[CURRENT_WORD_BUF];
    get_current_word(current_word);

    
    if (strlen(current_word) > 4) {
        memzero(current_word, sizeof(current_word));

        recovery_abort();
        fsm_sendFailure(FailureType_Failure_SyntaxError,
                        "STR");
        layoutHome();
        return;
    }

    CharacterRequest resp;
    memset(&resp, 0, sizeof(CharacterRequest));

    resp.word_pos = get_current_word_pos();
    resp.character_pos = strlen(current_word);

    msg_write(MessageType_MessageType_CharacterRequest, &resp);

    
    bool auto_completed = false;
    if (strlen(current_word) >= 3) {
        auto_completed = attempt_auto_complete(current_word);
    }

#if DEBUG_LINK
    if (auto_completed) {
        strlcpy(auto_completed_word, current_word, CURRENT_WORD_BUF);
    } else {
        auto_completed_word[0] = '\0';
    }
#endif

    
    format_current_word(current_word, auto_completed);

    
    layout_cipher(current_word, cipher);
    memzero(current_word, sizeof(current_word));
}