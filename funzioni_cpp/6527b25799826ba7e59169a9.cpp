static void use_numeric_locale(struct locale_context* context, char const* locale_name)
{
#ifdef HAVE_USELOCALE

    context->new_locale = newlocale(LC_NUMERIC_MASK, locale_name, NULL);
    context->old_locale = uselocale(context->new_locale);

#else

#if defined(HAVE__CONFIGTHREADLOCALE) && defined(_ENABLE_PER_THREAD_LOCALE)
    context->old_thread_config = _configthreadlocale(_ENABLE_PER_THREAD_LOCALE);
#endif

    context->category = LC_NUMERIC;
    tr_strlcpy(context->old_locale, setlocale(context->category, NULL), sizeof(context->old_locale));
    setlocale(context->category, locale_name);

#endif
}