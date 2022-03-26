void stringReplace(char* text, const char* pattern, char* replace)
{
	char newText[CAPACITY]; //extra space
	unsigned newTextIter = 0;

	char* textIter = text;

	unsigned replacedSize = strlen(replace);
	unsigned patternSize = strlen(pattern);

	while (*textIter != '\0')
	{
		if (isPrefix(textIter, pattern))
		{
			newText[newTextIter] = '\0'; //so strcat would work
			strcat(newText, replace);

			newTextIter += replacedSize;
			textIter += patternSize;
		}
		else
		{
			newText[newTextIter++] = *textIter;
			textIter++;
		}

	}
	newText[newTextIter] = '\0';
	strcpy(text, newText);
}
