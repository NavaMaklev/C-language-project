#include "project.h"
/*This method checks data rows.The method will return a false value in case of errors.*/
boolean lineOfData(char* current, type typeData, int line) {
	char dest[12];
	char ch;
	boolean notError;
	int number;
	int count;
	char* pointerNumber;
	count = 0;
	notError = TRUE;
	for (; *current == ' ' || *current == '\t'; ++current);
	if (typeData != DATA_ASCIZ) {/*db\dh\dw*/
		current = current + 3;
		ch = *current;
		for (; ch == ' ' || ch == '\t'; ch = *(++current));
		if (*current == ',' || *current == '\n') {
			printf("\nerror in line:%d there is no data.\n", line);
			notError = FALSE;
		}
		while (ch != '\n') {
			if (ch == '+') { ch = *(++current); }
			pointerNumber = current;
			while (isdigit(ch) || ch == '-') {
				ch = *(++current);
				count++;
			}
			if (count != 0) {
				strncpy(dest, pointerNumber, count);
				*(dest + count) = '\0';
				number = atoi(dest);
				count = 0;
				if (typeData == DATA_DB) {
					if (number < CHAR_MIN || number>CHAR_MAX) {
						printf("\nerror in line:%d the data not in the range.\n", line);
						notError = FALSE;
					}
				}

				if (typeData == DATA_DH) {
					if (number < SHRT_MIN || number>SHRT_MAX) {
						printf("\nerror in line:%d the data not in the range.\n", line);
						notError = FALSE;
					}
				}
				if (typeData == DATA_DW) {
					if (number < INT_MIN || number>INT_MAX) {
						printf("\nerror in line:%d the data not in the range.%d\n", line, number);
						notError = FALSE;
					}
				}
				enterData(typeData, number, line);
			}
			else {
				printf("\nerror in line:%d invalid input - there is no input after the comma.\n", line);
				notError = FALSE;
			}
			for (; ch == ' ' || ch == '\t'; ch = *(++current));
			if (*current == ',') {
				ch = *(++current);
				for (; ch == ' ' || ch == '\t'; ch = *(++current));
				if (ch == ',' || ch == '\n') {
					printf("\nsyntax error in line: %d - there is a comma without input. \n", line);
					notError = FALSE;
				}
			}
			for (; ch == ' ' || ch == '\t'; ch = *(++current));
		}
	}
	else {/*asciz*/
		count = 0;
		current = current + 6;/*jump over '.asciz'*/
		ch = *(current);
		for (; ch == ' ' || ch == '\t'; ch = *(++current));
		if (ch == '"') {
			ch = *(++current);
			while (ch != '"' && ch != '\n') {
				if (ch < 32 || ch>127) {
					printf("\nerror in line:%d the data asciz is not in the range.\n", line);
					notError = FALSE;
				}
				enterData(DATA_ASCIZ, ch, line);
				ch = *(++current);
				count++;

			}
			if (ch == '\n') {
				printf("\nerror in line:%d the string dont close.\n", line);
				notError = FALSE;
			}
			if (count == 0) {
				printf("\nerror in line:%d ,there is empty string.\n", line);
				notError = FALSE;
			}
			enterData(DATA_ASCIZ, '\0', line);
		}
		else { printf("\nerror in line:%d the string dont open.\n", line); notError = FALSE; }
	}
	return notError;
}
/*This method inserts data into the appropriate arrays.*/
void enterData(type dataType, int number, int line) {
	char sign;
	if (dataType == DATA_DB) {
		allocationForAllTheAction(DATA_DB, line);
		sign = 'b';
		dataB[numOfDataB - 1].numOfBits = number;
		dataB[numOfDataB - 1].address = DC;
		DC += SIZE_OF_BYTE;
	}
	else if (dataType == DATA_DH) {
		allocationForAllTheAction(DATA_DH, line);
		sign = 'h';
		dataH[numOfDataH - 1].numOfBits = number;
		dataH[numOfDataH - 1].address = DC;
		DC += SIZE_OF_HALF_WORD;
	}
	else if (dataType == DATA_DW) {
		allocationForAllTheAction(DATA_DW, line);
		sign = 'w';
		dataW[numOfDataW - 1].numOfBits = number;
		dataW[numOfDataW - 1].address = DC;
		DC += SIZE_OF_WORD;
	}
	else {
		allocationForAllTheAction(DATA_DB, line);
		sign = 'a';
		dataB[numOfDataB - 1].numOfBits = number;
		dataB[numOfDataB - 1].address = DC;
		DC += SIZE_OF_BYTE;
	}
	allocationForAllTheAction(SIGN, line);
	symbolData[sumOfCharacters - 1] = sign;
}
