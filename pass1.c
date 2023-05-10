#include "project.h"
boolean stage1(FILE* file) {
	char line[MAX_LINE];/*arr for current line*/
	char label[MAX_LABEL];
	char codeArr[] = { "code\0" };
	char dataArr[] = { "data\0" };
	char externArr[] = { "external\0" };
	char* pointerlabel;
	char* current;/*pointer for current line*/
	int countWhiteSpace;
	char* externLabel;
	int numberOfLine;
	int countLabel;
	boolean erorrFlag;
	boolean if_label;
	type typeword;
	countLabel = 0;
	numberOfLine = 1;
	countWhiteSpace = 0;
	if_label = FALSE;/*flag for label*/
	erorrFlag = FALSE;
	while (feof(file) == 0) {
		fgets(line, MAX_LINE, file);
		if (feof(file) == 1)
			break;
		current = line;
		typeword = typeWord(current, &countWhiteSpace, numberOfLine);
		if (typeword == LABEL) {
			if_label = TRUE;/*line with label*/
			pointerlabel = getlable(current, &countLabel);
			strcpy(label, pointerlabel);
			current += strlen(label) + countLabel + 1;
			if (typeWord(current, &countWhiteSpace, numberOfLine) == EXTERN)
				if_label = FALSE;
		}
		countWhiteSpace = 0;
		typeword = typeWord(current, &countWhiteSpace, numberOfLine);
		if (typeword == END || typeword == NOTE || typeword == ENTRY) {/*The row will be advanced at the end of the loop*/ }
		else if (typeword == EXTERN) {
			externLabel = legalsymbol(current + countWhiteSpace, FALSE, FALSE, numberOfLine);
			if (externLabel == NULL) {
				printf("\nthere is not extern name label.\n");
				erorrFlag = TRUE;
			}
			if (checkEntryOrExternLine(current, FALSE, numberOfLine, strlen(externLabel)) == FALSE)erorrFlag = TRUE;
			if (enterInTable(externLabel, 0, TRUE, externArr, numberOfLine) == FALSE) {
				erorrFlag = TRUE;
			}
		}
		/*line of data*/
		else if (typeword == DATA_ASCIZ || typeword == DATA_DW || typeword == DATA_DH || typeword == DATA_DB) {
			if (if_label == TRUE) {
				if (enterInTable(label, DC, FALSE, dataArr, numberOfLine) == FALSE) {
					erorrFlag = TRUE;
				}
			}

			if (lineOfData(current, typeword, numberOfLine) == FALSE) {
				erorrFlag = TRUE;
			}
		}
		else/*line of code*/
		{
			if (if_label == TRUE) {
				if (enterInTable(label, IC, FALSE, codeArr, numberOfLine) == FALSE) {
					erorrFlag = TRUE;
				}
			}
			if (lineOfCode(current, numberOfLine) == FALSE) {
				erorrFlag = TRUE;
			}
		}
		if_label = FALSE;
		numberOfLine++;
	}

	if (erorrFlag == TRUE) {
		return TRUE;
	}
	updateAdress();
	return FALSE;

}
/*this method update the address*/
void updateAdress() {
	int i;
	ICF = IC;
	DCF = DC;
	for (i = 0; i < numOfLabels; i++) {
		if (strcmp(symbol_table[i].attributes, "data") == 0)
			symbol_table[i].value += ICF;
	}
	for (i = 0; i < numOfDataB; i++) {
		dataB[i].address += ICF;
	}
	for (i = 0; i < numOfDataH; i++) {
		dataH[i].address += ICF;
	}
	for (i = 0; i < numOfDataW; i++) {
		dataW[i].address += ICF;
	}
}
/*method returns which type the word in the current line*/
type typeWord(char* start, int* countWhiteSpace, int line) {
	char str[MAX_LABEL];
	int i;
	while ((*start == ' ') || (*start == '\t')) {/*jump space*/
		start++;
		(*countWhiteSpace)++;
	}
	if (*start == '\n')
		return END;
	if (*start == ';')
		return NOTE;
	for (i = 0; (*start != ' ') && (*start != '\t') && (*start != '\n'); i++, start++)
		str[i] = *start;
	str[i] = '\0';
	if ((strcmp(str, ".dh")) == 0)
		return DATA_DH;
	if ((strcmp(str, ".dw")) == 0)
		return DATA_DW;
	if ((strcmp(str, ".db")) == 0)
		return DATA_DB;
	if ((strcmp(str, ".asciz")) == 0)
		return DATA_ASCIZ;
	if ((strcmp(str, ".extern")) == 0)
		return EXTERN;
	if ((strcmp(str, ".entry")) == 0)
		return ENTRY;
	if (islabel(str, line) == TRUE)
		return LABEL;
	return OTHER;/*to line of code*/
}

/*method return true when the line of entry or external is legal*/
boolean checkEntryOrExternLine(char* current, boolean isEntry, int line, int lengthLabel) {
	if (isEntry == TRUE)
		current += 6;/*jump over '.entry'*/
	else
		current += 7;/*jump over '.extern'*/
	for (; *current == ' ' || *current == '\t'; (++current));
	current += lengthLabel;
	for (; *current == ' ' || *current == '\t'; (++current));
	if (*current != '\n') { printf("\nerror in line:%d ,invalid input.\n", line); return FALSE; }
	return TRUE;
}
