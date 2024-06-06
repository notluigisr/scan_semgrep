addCharacterClass(FileInfo *nested, const widechar *name, int length,
		CharacterClass **characterClasses,
		TranslationTableCharacterAttributes *characterClassAttribute) {
	
	CharacterClass *class;
	if (*characterClassAttribute) {
		if (!(class = malloc(sizeof(*class) + CHARSIZE * (length - 1))))
			_lou_outOfMemory();
		else {
			memset(class, 0, sizeof(*class));
			memcpy(class->name, name, CHARSIZE * (class->length = length));
			class->attribute = *characterClassAttribute;
			*characterClassAttribute <<= 1;
			class->next = *characterClasses;
			*characterClasses = class;
			return class;
		}
	}
	compileError(nested, "STR");
	return NULL;
}