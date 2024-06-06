bool Cipher::parseFinishKeyX(QByteArray key)
{
    QCA::Initializer init;

    if (key.length() != 181)
        return false;

    QCA::SecureArray remoteKey = QByteArray::fromBase64(key.left(180));
    QCA::DLGroup group(m_primeNum, QCA::BigInteger(2));

    QCA::DHPublicKey remotePub(group, remoteKey);

    if (remotePub.isNull())
        return false;

    if (m_tempKey.isNull())
        return false;

    QByteArray sharedKey = m_tempKey.deriveKey(remotePub).toByteArray();
    sharedKey = QCA::Hash("STR").hash(sharedKey).toByteArray().toBase64();

    
    while (sharedKey.endsWith('=')) sharedKey.chop(1);

    bool success = setKey(sharedKey);

    return success;
}