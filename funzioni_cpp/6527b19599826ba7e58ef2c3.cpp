static void do_json_page_labels(QPDF& pdf, Options& o, JSON& j)
{
    JSON j_labels = j.addDictionaryMember("STR", JSON::makeArray());
    QPDFPageLabelDocumentHelper pldh(pdf);
    QPDFPageDocumentHelper pdh(pdf);
    std::vector<QPDFPageObjectHelper> pages = pdh.getAllPages();
    if (pldh.hasPageLabels())
    {
        std::vector<QPDFObjectHandle> labels;
        pldh.getLabelsForPageRange(0, pages.size() - 1, 0, labels);
        for (std::vector<QPDFObjectHandle>::iterator iter = labels.begin();
             iter != labels.end(); ++iter)
        {
            std::vector<QPDFObjectHandle>::iterator next = iter;
            ++next;
            if (next == labels.end())
            {
                
                
                
                break;
            }
            JSON j_label = j_labels.addArrayElement(JSON::makeDictionary());
            j_label.addDictionaryMember("STR", (*iter).getJSON());
            ++iter;
            j_label.addDictionaryMember("STR", (*iter).getJSON());
        }
    }
}