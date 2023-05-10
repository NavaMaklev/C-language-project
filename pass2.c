#include "project.h"
boolean stage2(FILE* fd2) {
    boolean notError = TRUE;
    int line;
    char arrline[MAX_LINE];
    char* entrys;
    char* labelName;
    char* current;
    int countLine;
    int countWhiteSpace;
    int countSpace;
    type  wordtype;
    countSpace = 0;
    line = 1;
    while (feof(fd2) == 0) {
        fgets(arrline, MAX_LINE, fd2);
        if (feof(fd2) == 1) {
            break;
        }
        current = arrline; /* pointer to the current position in row */
        countWhiteSpace = 0;
        wordtype = typeWord(current, &countWhiteSpace, line);
        if (wordtype == LABEL) {
            labelName = getlable(current, &countSpace); /* get the name of the label */
            current += strlen(labelName) + countSpace + 1; /* updates the current position in the row - after the label */
            countWhiteSpace = 0;
            wordtype = typeWord(current, &countWhiteSpace, line); /* skips the label */
        }
        if (wordtype == NOTE || wordtype == END) /* chek if the line is an empty line */
            line++;
        else if ((wordtype == EXTERN) || (wordtype == DATA_ASCIZ) || (wordtype == DATA_DB) || (wordtype == DATA_DH) || (wordtype == DATA_DW))
            line++;
        else if (wordtype == ENTRY) {
            entrys = legalsymbol(current, TRUE, FALSE, line);
            if (entrys == NULL) {
                printf("\nerror in line:%d entry without label.\n", line);
                notError = FALSE;
            }
            if (checkEntryOrExternLine(current, TRUE, line, strlen(entrys)) == FALSE)notError = FALSE;
            countLine = 0;
            if (notintable(&countLine, entrys) == TRUE) {
                printf("\neror: in line %d export a non-existent label\n", line);
                notError = FALSE;
            }
            else if (strcmp(symbol_table[countLine].attributes, "external") != 0) {
                symbol_table[countLine].entry = TRUE;
                entrySymbol++;
            }
            else {
                printf("\neror: in line %d export a non-existent label\n", line);
                notError = FALSE;
            }
            line++;
        }

        else {/*line of code.*/
            if (lineOfCode2(current, line) == FALSE) {
                notError = FALSE;
            }
            line++;
            IC2 += 4;
        }
    }
    if (notError == FALSE)
        return TRUE;
    return FALSE;
}

