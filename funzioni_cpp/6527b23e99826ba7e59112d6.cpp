void AuthorizationManager::invalidateUsersFromDB(const std::string& dbname) {
    CacheGuard guard(this, CacheGuard::fetchSynchronizationManual);
    _updateCacheGeneration_inlock();
    unordered_map<UserName, User*>::iterator it = _userCache.begin();
    while (it != _userCache.end()) {
        User* user = it->second;
        if (user->getName().getDB() == dbname) {
            _userCache.erase(it++);
            user->invalidate();
        } else {
            ++it;
        }
    }
}