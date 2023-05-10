#include "project.h"
/* check if label is legal */
boolean islabel(char word[], int line) {
	int i;
	if (word[strlen(word) - 1] != ':') {
		return FALSE;
	}
	if (isalpha(word[0]))
	{
		for (i = 1; i < (strlen(word) - 1); i++)
			if ((!(isalpha(word[i]))) && (!(isdigit(word[i])))) {
				return FALSE;
			}

	}
	/*check if the label is a keep word*/
	word[strlen(word) - 1] = '\0';
	for (i = 0;i < 27;i++) {
		if (strcmp(allActions[i].methodName, word) == 0) { return FALSE; }
	}
	if (strcmp(word, "db") == 0) { return FALSE; }
	if (strcmp(word, "dh") == 0) { return FALSE; }
	if (strcmp(word, "dw") == 0) { return FALSE; }
	if (strcmp(word, "asciz") == 0) { return FALSE; }
	return TRUE;
}
/*This method checks whether the label for entry is not in the table of symbols,
If the label is found the method will return the value true.
In case the label is not in the table the method will call the insert method and the label will be added to the symbol table.*/
boolean enterInTable(char* name, int address, boolean isExternal, char type[], int line) {
	int count = 0;
	if ((notintable(&count, name)) == FALSE) {
		if (isExternal == TRUE) {
			if (strcmp(symbol_table[count].attributes, "external") != 0) {
				printf("\nerror in line: %d, there is the same label name in the table without external.\n", line);
				return FALSE;
			}
			else {
				printf("\nerror in line: %d the label is exist.\n", line);
				return FALSE;
			}
		}
		else {
			printf("\nerror in line: %d the label is exist.\n", line);
			return FALSE;
		}
	}
	else {
		allocationForAllTheAction(LABEL, line);
		strcpy(symbol_table[numOfLabels - 1].symbol, name);
		symbol_table[numOfLabels - 1].value = address;
		strcpy(symbol_table[numOfLabels - 1].attributes, type);
		return TRUE;
	}

}
/*this method return the label*/
char* getlable(char start[], int* j) {
	/* return the label */
	static char label[MAX_LABEL];
	int i;
	while ((*start == ' ') || (*start == '\t'))
	{
		start++;
		(*j)++;
	}
	for (i = 0; (start[i] != ':'); i++)
		label[i] = start[i];
	label[i] = '\0';
	return label;
}
/* check if symbol is'nt in symbol-table, holds a pointer to the position of the label in the table */
boolean notintable(int* countLine, char namel[]) {
	int i;
	(*countLine) = 0;
	for (i = 0; i < numOfLabels; i++) {
		if (strcmp(symbol_table[i].symbol, namel) == 0) {
			return FALSE;
		}
		(*countLine)++;
	}
	return TRUE;
}
/* check if  label is legal */
char* legalsymbol(char* start, boolean isEntry, boolean pass2, int line) {
	static char str[MAX_LABEL];
	int i;
	while (((*start) == ' ') || ((*start) == '\t'))
		start++;
	if (isEntry == FALSE && pass2 == FALSE)
		start += 7;/*if its extern label*/
	else if (isEntry == TRUE && pass2 == FALSE)
		start += 6;/*if its entry label*/
	while ((*start == ' ') || (*start == '\t'))
		start++;
	for (i = 0; (*start != ' ') && (*start != '\t') && (*start != '\n'); i++, start++)
		str[i] = *start;
	str[i] = ':';
	str[i + 1] = '\0';
	if (islabel(str, line) == TRUE) {
		str[i] = '\0';
		return str;
	}
	return NULL;
}
