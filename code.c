#include "project.h"
/*This method sends to test methods according to the type of instruction in the current line (R\I\J).
The method will return a false value in case of errors.
 */
boolean lineOfCode(char* current, int numberOfLine) {
    int i;
    int indexAction = -1;
    char typeAction[MAX_LABEL];
    for (; *current == ' ' || *current == '\t'; (++current));
    for (i = 0; (*current != ' ' && *current != '\t' && *current != '\n') && i < MAX_LABEL; (++current), i++) {
        typeAction[i] = *current;
    }
    typeAction[i] = '\0';
    if ((*current) == '\n' || i > 5) {
        printf("\nerror in line %d,there is no input.\n", numberOfLine);
        return FALSE;
    }
    for (i = 0; i < 27 && indexAction == -1; i++) {/*check if the action exist*/
        if (strcmp(typeAction, allActions[i].methodName) == 0) {
            indexAction = i;
        }
    }
    if (indexAction == -1) {
        printf("\nerror in line %d,invalid input - the name action not exist.\n", numberOfLine);
        return FALSE;
    }
    else {

        for (; *current == ' ' || *current == '\t'; (++current));
        if (allActions[indexAction].methodType == 'R')
            if ((checkLineOfR(current, indexAction, numberOfLine)) == FALSE) { return FALSE; }
        if (allActions[indexAction].methodType == 'I')
            if ((checkLineOfI(current, indexAction, numberOfLine)) == FALSE) { return FALSE; }
        if (allActions[indexAction].methodType == 'J')
            if ((checkLineOfJ(current, indexAction, numberOfLine)) == FALSE) { return FALSE; }
        IC += 4;
    }
    return TRUE;
}
/*This method check R instruction.*/
boolean checkLineOfR(char* current, int index, int numberOfLine) {
    int countRegister = 0;
    int countDigits = 0;
    int i = 0;
    char ch = *current;
    char stringNumber[12];
    char* pointerNumber;
    int numbers[4];
    if (ch != '$') { printf("\nerror in line %d,invalid input - input without sign '$'.\n", numberOfLine); return FALSE; }
    else { ch = *(++current); }
    while (ch != '\n' && ch != '\t' && ch != ' ' && countRegister < 4) {
        pointerNumber = current;
        while (isdigit(ch)) {
            countDigits++;
            ch = *(++current);
        }
        if (countDigits) {
            strncpy(stringNumber, pointerNumber, countDigits);
            stringNumber[countDigits] = '\0';
            countDigits = 0;
            numbers[i++] = atoi(stringNumber);
            countRegister++;
        }
        else {/*countdigit==0.*/
            printf("\nerror in line %d,invalid input - no input after the comma.\n", numberOfLine);
            return FALSE;
        }
        for (; ch == ' ' || ch == '\t'; ch = *(++current));
        if (ch == ',' && countRegister == allActions[index].help) { printf("\nerror in line %d,invalid input - there is extra comma.\n", numberOfLine); return FALSE; }
        if (ch == '\n' && countRegister < allActions[index].help) { printf("\nerror in line %d,invalid input - few registers.\n", numberOfLine); return FALSE; }
        if (ch != ',' && countRegister < allActions[index].help) { printf("\nerror in line %d,invalid input - few registers.\n", numberOfLine); return FALSE; }
        if (ch == ',') {
            ch = *(++current);
            for (; ch == ' ' || ch == '\t'; ch = *(++current));
            if (ch != '$') { printf("\nerror in line %d,invalid input - input without sign '$'.\n", numberOfLine); return FALSE; }
            ch = *(++current);
        }
    }

    if (countRegister == allActions[index].help) {/*insert input.*/
        allocationForAllTheAction(OTHER, numberOfLine);
        instruction_table[numOfInstruction - 1].rAction.opcode = allActions[index].opcode;
        instruction_table[numOfInstruction - 1].rAction.funct = allActions[index].funct;
        instruction_table[numOfInstruction - 1].rAction.notUsing = 0;
        instruction_table[numOfInstruction - 1].rAction.address = IC;
        if (allActions[index].help == 3) {
            instruction_table[numOfInstruction - 1].rAction.rs = numbers[0];
            instruction_table[numOfInstruction - 1].rAction.rt = numbers[1];
            instruction_table[numOfInstruction - 1].rAction.rd = numbers[2];
        }
        else {
            instruction_table[numOfInstruction - 1].rAction.rs = numbers[0];
            instruction_table[numOfInstruction - 1].rAction.rd = numbers[1];
            instruction_table[numOfInstruction - 1].rAction.rt = 0;
        }
        return TRUE;
    }
    printf("\nerror in line %d,invalid input.\n", numberOfLine);
    return FALSE;
}
/*This method check I instruction.*/
boolean checkLineOfI(char* current, int index, int numberOfLine) {
    if (allActions[index].help != 2) {
        int countRegister = 0;
        int countDigits = 0;
        int i = 0;
        char ch = *current;
        char stringNumber[12];
        char* pointerNumber;
        int numbers[4];
        if (ch != '$') { printf("\nerror in line %d,invalid input - input without sign '$'.\n", numberOfLine); return FALSE; }
        else { ch = *(++current); }
        while (ch != '\n' && ch != '\t' && ch != ' ' && countRegister < 5) {
            if (ch == '+')
                ch = *(++current);
            pointerNumber = current;
            while (isdigit(ch) || ch == '-') {
                countDigits++;
                ch = *(++current);
            }
            if (countDigits) {
                strncpy(stringNumber, pointerNumber, countDigits);
                stringNumber[countDigits] = '\0';
                countDigits = 0;
                numbers[i++] = atoi(stringNumber);
                countRegister++;
            }
            else {/*countdigits==0.*/
                printf("\nerror in line %d,invalid input - extra comma.\n", numberOfLine);
                return FALSE;
            }
            for (; ch == ' ' || ch == '\t'; ch = *(++current));
            if (ch == ',' && countRegister == 3) { printf("\nerror in line %d,invalid input - extra comma\n", numberOfLine); return FALSE; }
            if (ch == '\n' && countRegister < 3) { printf("\nerror in line %d,invalid input - few registers.\n", numberOfLine); return FALSE; }
            if (ch != ',' && countRegister < 3) { printf("\nerror in line %d,invalid input - there is no comma.\n", numberOfLine); return FALSE; }
            if (ch == ',') {
                ch = *(++current);
                for (; ch == ' ' || ch == '\t'; ch = *(++current));
                if (ch != '$' && countRegister != 1) { printf("\nerror in line %d,invalid input - no sign '$'.\n", numberOfLine); return FALSE; }
                if (countRegister != 1 && ch == '$')
                    ch = *(++current);
                if (ch == '$' && countRegister == 1) { printf("\nerror in line %d,invalid input - extra '$'.\n", numberOfLine); return FALSE; }
            }
        }
        if (countRegister == 3) {/*insert input.*/
            allocationForAllTheAction(OTHER, numberOfLine);
            instruction_table[numOfInstruction - 1].iAction.opcode = allActions[index].opcode;
            instruction_table[numOfInstruction - 1].iAction.rs = numbers[0];
            instruction_table[numOfInstruction - 1].iAction.immed = numbers[1];
            instruction_table[numOfInstruction - 1].iAction.rt = numbers[2];
            instruction_table[numOfInstruction - 1].iAction.address = IC;
            return TRUE;
        }
        printf("\nerror in line %d,invalid input.\n", numberOfLine);
        return FALSE;
    }
    else {
        /*Treated in the second pass*/
        allocationForAllTheAction(OTHER, numberOfLine);
        instruction_table[numOfInstruction - 1].iAction.address = IC;
    }
    return TRUE;
}
/*This method check J instruction.*/
boolean checkLineOfJ(char* current, int index, int numberOfLine) {
    /*Treated in the second pass*/
    allocationForAllTheAction(OTHER, numberOfLine);
    instruction_table[numOfInstruction - 1].jAction.addressIC = IC;
    return TRUE;
}
/*This method is activated in the second transition.
The method sends to test methods only instructions that were not addressed in the first transition.
The method will return a false value in case of an error.
*/
boolean lineOfCode2(char* current, int line) {
    int i;
    int indexAction = -1;
    char typeAction[MAX_LABEL];
    for (; *current == ' ' || *current == '\t'; (++current));
    for (i = 0; (*current != ' ' && *current != '\t' && *current != '\n') && i < MAX_LABEL; (++current), i++) {
        typeAction[i] = *current;
    }
    typeAction[i] = '\0';
    if ((*current) == '\n' || i > 6)return FALSE;
    for (i = 0; i < 27 && indexAction == -1; i++) {
        if (strcmp(typeAction, allActions[i].methodName) == 0) {
            indexAction = i;
        }
    }
    if (indexAction == -1)return FALSE;
    else {
        for (; *current == ' ' || *current == '\t'; (++current));
        if (allActions[indexAction].methodType == 'R') return TRUE;
        if (allActions[indexAction].methodType == 'I' && allActions[indexAction].help == 2)
            if ((checkLineOfI2(current, indexAction, line)) == FALSE) { return FALSE; }
        if (allActions[indexAction].methodType == 'J')
            if ((checkLineOfJ2(current, indexAction, line)) == FALSE) { return FALSE; }

        return TRUE;
    }
}
/*This method is activated in the second transition and check line of I instruction.*/
boolean checkLineOfI2(char* current, int indexAction, int line) {
    char externArr[] = { "external\0" };
    char ch = *current;
    char* labels;
    int countRegister = 0, countDigits = 0, i = 0, place = (IC2 - 100) / 4, countLines = 0, addressLabel = 0;
    char* pointerNumber;
    char stringNumber[12];
    int numbers[2];
    char labelName[MAX_LABEL];
    if (ch != '$') { printf("\n error in line:%d invalid input - no sign '$'.\n", line); return FALSE; }
    else { ch = *(++current); }
    while (ch != '\n' && ch != '\t' && ch != ' ' && countRegister < 2 && ch != ',') {
        if (ch == '+')
            ch = *(current++);
        pointerNumber = current;
        while (isdigit(ch) || ch == '-') {
            countDigits++;
            ch = *(++current);
        }
        if (countDigits) {
            strncpy(stringNumber, pointerNumber, countDigits);
            stringNumber[countDigits] = '\0';
            countDigits = 0;
            numbers[i++] = atoi(stringNumber);
            countRegister++;
        }
        else {
            printf("\n error in line:%d invalid input - extra comma or no input.\n", line);
            return FALSE;
        }
        for (; ch == ' ' || ch == '\t'; ch = *(++current));
        if (ch == '\n' && countRegister < 3) { printf("\n error in line:%d invalid input - few registers.\n", line); return FALSE; }
        if (ch == ',' && countRegister < 2) {
            ch = *(++current);
            for (; ch == ' ' || ch == '\t'; ch = *(++current));
            if (ch != '$' && countRegister != 2) { printf("\n error in line:%d invalid input - no '$'.\n", line); return FALSE; }
            if (countRegister != 2 && ch == '$') { ch = *(++current); }
            if (ch == '$' && countRegister == 2) { printf("\n error in line:%d invalid input - extra '$'\n", line); return FALSE; }
        }
    }
    if (countRegister == 2 && ch == ',') {
        current++;
        labels = legalsymbol(current, FALSE, TRUE, line);
        for (; *current == ' ' || *current == '\t'; (++current));
        if (labels == NULL) {
            printf("\n error in line:%d invalid input - there is not label.\n", line);
            return FALSE;
        }
        strcpy(labelName, labels);
        countLines = 0;
        if (notintable(&countLines, labelName) == TRUE) {
            printf("\n error in line:%d the label not exist in the table\n", line);
            return FALSE;
        }
        current += strlen(labelName);
        ch = *current;
        for (; ch == ' ' || ch == '\t'; ch = *(++current));
        if (ch == '\n' && (strcmp(symbol_table[countLines].attributes, externArr) != 0)) {
            addressLabel = symbol_table[countLines].value;
            addressLabel -= IC2;
            instruction_table[place].iAction.opcode = allActions[indexAction].opcode;
            instruction_table[place].iAction.rs = numbers[0];
            instruction_table[place].iAction.immed = addressLabel;
            instruction_table[place].iAction.rt = numbers[1];
            return TRUE;
        }
    }
    printf("\n error in line:%d invalid input\n", line);
    return FALSE;
}
/*This method is activated in the second transition and check line of J instruction.*/
boolean checkLineOfJ2(char* current, int indexAction, int line) {
    int address = 0, reg = 0, opcode = 0, countline = 0, countDigits = 0, number = 0;
    int place = (IC2 - 100) / 4;
    char* labelName = NULL;
    char* pointerNumber = NULL;
    char stringNumber[12];
    char labelArr[MAX_LABEL];
    boolean useExternalLabel = FALSE;
    if (allActions[indexAction].help == 0) {/*stop action*/
        if (*current != '\n') {
            printf("\n error in line:%d invalid input - extra input.\n", line);
            return FALSE;
        }
        opcode = allActions[indexAction].opcode;
    }
    else if (allActions[indexAction].help == 1) {/*la or call action*/
        labelName = legalsymbol(current, FALSE, TRUE, line);
        if (labelName == NULL) { printf("\n error in line:%d there is not label after the action.\n", line); return FALSE; }
        strcpy(labelArr, labelName);
        if (notintable(&countline, labelArr) == TRUE) { printf("\n error in line:%d this label not exist.\n", line); return FALSE; }
        current += strlen(labelArr) + 1;
        for (; *current == ' ' || *current == '\t'; current++);
        if (*current != '\n') { printf("\n error in line:%d invalid input - extra input.\n", line); return FALSE; }
        if (strcmp(symbol_table[countline].attributes, "external") == 0) { useExternalLabel = TRUE; }
        reg = 0;
        address = symbol_table[countline].value;
        opcode = allActions[indexAction].opcode;
    }
    else {/*jmp action*/
        if (*current == '$') {
            current++;
            pointerNumber = current;
            while (isdigit(*current)) {
                countDigits++;
                current++;
            }
            if (countDigits != 0) {
                strncpy(stringNumber, pointerNumber, countDigits);
                stringNumber[countDigits] = '\0';
                countDigits = 0;
                number = atoi(stringNumber);
            }
            else { printf("\n error in line:%d invalid input - there is '$' without input.\n", line); return FALSE; }
            for (; *current == ' ' || *current == '\t'; current++);
            if (*current != '\n') { printf("\n error in line:%d invalid input - extra input.\n", line); return FALSE; }
            reg = 1;
            address = number;
            opcode = allActions[indexAction].opcode;
        }
        else {
            labelName = legalsymbol(current, FALSE, TRUE, line);
            if (labelName == NULL) { printf("\n error in line:%d there is not label after the action.\n", line); return FALSE; }
            strcpy(labelArr, labelName);
            if (notintable(&countline, labelArr) == TRUE) { printf("\n error in line:%d this label not exist.\n", line); return FALSE; }
            current += strlen(labelArr);
            for (; *current == ' ' || *current == '\t'; current++);
            if (*current != '\n') { printf("\n error in line:%d invalid input - extra input.\n", line); return FALSE; }


            if (strcmp(symbol_table[countline].attributes, "external") == 0) { useExternalLabel = TRUE; }
            reg = 0;
            address = symbol_table[countline].value;
            opcode = allActions[indexAction].opcode;
        }
    }
    /*insert input.*/
    instruction_table[place].jAction.reg = reg;
    instruction_table[place].jAction.opcode = opcode;
    instruction_table[place].jAction.address = address;
    if (useExternalLabel == TRUE) {/*insert input for extern file.ext.*/
        allocationForAllTheAction(EXTERN, line);
        strcpy(external_symbol[externSymbol - 1].labelName, labelArr);
        external_symbol[externSymbol - 1].address = instruction_table[place].jAction.addressIC;
    }
    return TRUE;
}








