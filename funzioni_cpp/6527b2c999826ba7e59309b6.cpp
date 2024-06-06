ReturnCode_t DataWriterImpl::get_offered_deadline_missed_status(
        OfferedDeadlineMissedStatus& status)
{
    if (writer_ == nullptr)
    {
        return ReturnCode_t::RETCODE_NOT_ENABLED;
    }

    std::unique_lock<RecursiveTimedMutex> lock(writer_->getMutex());

    status = deadline_missed_status_;
    deadline_missed_status_.total_count_change = 0;
    return ReturnCode_t::RETCODE_OK;
}