static void do_json_acroform(QPDF& pdf, Options& o, JSON& j)
{
    JSON j_acroform = j.addDictionaryMember(
        "STR", JSON::makeDictionary());
    QPDFAcroFormDocumentHelper afdh(pdf);
    j_acroform.addDictionaryMember(
        "STR",
        JSON::makeBool(afdh.hasAcroForm()));
    j_acroform.addDictionaryMember(
        "STR",
        JSON::makeBool(afdh.getNeedAppearances()));
    JSON j_fields = j_acroform.addDictionaryMember(
        "STR", JSON::makeArray());
    QPDFPageDocumentHelper pdh(pdf);
    std::vector<QPDFPageObjectHelper> pages = pdh.getAllPages();
    int pagepos1 = 0;
    for (std::vector<QPDFPageObjectHelper>::iterator page_iter =
             pages.begin();
         page_iter != pages.end(); ++page_iter)
    {
        ++pagepos1;
        std::vector<QPDFAnnotationObjectHelper> annotations =
            afdh.getWidgetAnnotationsForPage(*page_iter);
        for (std::vector<QPDFAnnotationObjectHelper>::iterator annot_iter =
                 annotations.begin();
             annot_iter != annotations.end(); ++annot_iter)
        {
            QPDFAnnotationObjectHelper& aoh = *annot_iter;
            QPDFFormFieldObjectHelper ffh =
                afdh.getFieldForAnnotation(aoh);
            JSON j_field = j_fields.addArrayElement(
                JSON::makeDictionary());
            j_field.addDictionaryMember(
                "STR",
                ffh.getObjectHandle().getJSON());
            j_field.addDictionaryMember(
                "STR",
                ffh.getObjectHandle().getKey("STR").getJSON());
            j_field.addDictionaryMember(
                "STR",
                JSON::makeInt(pagepos1));
            j_field.addDictionaryMember(
                "STR",
                JSON::makeString(ffh.getFieldType()));
            j_field.addDictionaryMember(
                "STR",
                JSON::makeInt(ffh.getFlags()));
            j_field.addDictionaryMember(
                "STR",
                JSON::makeString(ffh.getFullyQualifiedName()));
            j_field.addDictionaryMember(
                "STR",
                JSON::makeString(ffh.getPartialName()));
            j_field.addDictionaryMember(
                "STR",
                JSON::makeString(ffh.getAlternativeName()));
            j_field.addDictionaryMember(
                "STR",
                JSON::makeString(ffh.getMappingName()));
            j_field.addDictionaryMember(
                "STR",
                ffh.getValue().getJSON());
            j_field.addDictionaryMember(
                "STR",
                ffh.getDefaultValue().getJSON());
            j_field.addDictionaryMember(
                "STR",
                JSON::makeInt(ffh.getQuadding()));
            j_field.addDictionaryMember(
                "STR",
                JSON::makeBool(ffh.isCheckbox()));
            j_field.addDictionaryMember(
                "STR",
                JSON::makeBool(ffh.isRadioButton()));
            j_field.addDictionaryMember(
                "STR",
                JSON::makeBool(ffh.isChoice()));
            j_field.addDictionaryMember(
                "STR",
                JSON::makeBool(ffh.isText()));
            JSON j_choices = j_field.addDictionaryMember(
                "STR", JSON::makeArray());
            std::vector<std::string> choices = ffh.getChoices();
            for (std::vector<std::string>::iterator iter = choices.begin();
                 iter != choices.end(); ++iter)
            {
                j_choices.addArrayElement(JSON::makeString(*iter));
            }
            JSON j_annot = j_field.addDictionaryMember(
                "STR", JSON::makeDictionary());
            j_annot.addDictionaryMember(
                "STR",
                aoh.getObjectHandle().getJSON());
            j_annot.addDictionaryMember(
                "STR",
                JSON::makeString(aoh.getAppearanceState()));
            j_annot.addDictionaryMember(
                "STR",
                JSON::makeInt(aoh.getFlags()));
        }
    }
}