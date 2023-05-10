#include"project.h"
/*Allocation method for data type db*/
void allocationOfMemoryToDataB(int line) {
	if (numOfDataB++ == 0) {
		dataB = (db*)malloc(START_MEMORY * sizeof(db));
		if (dataB == NULL) {
			printf("\nerror in line: %d Allocation failed. \n", line);
			exit(1);
		}
	}
	else
	{
		dataB = (db*)realloc(dataB, (START_MEMORY + (numOfDataB + 1)) * sizeof(db));
		if (dataB == NULL) {
			printf("\nerror in line: %d Allocation failed.\n", line);
			exit(1);
		}
	}
}
/*Allocation method for data type dh*/
void allocationOfMemoryToDataH(int line) {
	if (numOfDataH++ == 0) {
		dataH = (dh*)malloc(START_MEMORY * sizeof(dh));
		if (dataH == NULL) {
			printf("\nerror in line: %d Allocation failed. \n", line);
			exit(1);
		}
	}
	else {
		dataH = (dh*)realloc(dataH, (START_MEMORY + numOfDataH + 1) * sizeof(dh));
		if (dataH == NULL) {
			printf("\nerror in line: %d Allocation failed \n", line);
			exit(1);
		}
	}
}
/*Allocation method for data type dw*/
void allocationOfMemoryToDataW(int line) {
	if (numOfDataW++ == 0) {
		dataW = (dw*)malloc(START_MEMORY * sizeof(dw));
		if (dataW == NULL) {
			printf("\nerror in line: %d Allocation failed. \n", line);
			exit(1);
		}
	}
	else {
		dataW = (dw*)realloc(dataW, (START_MEMORY + numOfDataW + 1) * sizeof(dw));
		if (dataW == NULL) {
			printf("\nerror in line: %d Allocation failed. \n", line);
			exit(1);
		}
	}
}
/*Allocation method for labels*/
void allocationOfMemoryToSymbolData(int line) {
	if (sumOfCharacters++ == 0) {
		symbolData = (char*)malloc(START_MEMORY * sizeof(char));
		if (symbolData == NULL) {
			printf("\nerror in line:%d Allocation failed. \n", line);
			exit(1);
		}
	}
	else {
		symbolData = (char*)realloc(symbolData, (START_MEMORY + sumOfCharacters + 1) * sizeof(char));
		if (symbolData == NULL) {
			printf("\nerror in line:%d Allocation failed \n", line);
			exit(1);
		}
	}
}
/*Allocation method for symbol data array.
this array including characters according the data type that will insert to the Data image*/
void allocationOfMemoryToSymbolTable(int line) {
	if (numOfLabels++ == 0) {
		symbol_table = (label*)malloc(START_MEMORY * sizeof(label));
		if (symbol_table == NULL) {
			printf("\nerror in line:%d  malloc Allocation failed.\n", line);
			exit(1);
		}
	}
	else {
		symbol_table = (label*)realloc(symbol_table, (START_MEMORY + numOfLabels + 1) * sizeof(label));
		if (symbol_table == NULL) {
			printf("\nerror in line: %d Allocation failed. \n", line);
			exit(1);
		}
	}
}
/*Allocation method for Instruction Table*/
void allocationOfMemoryToInstructionTable(int line) {
	if (numOfInstruction++ == 0) {
		instruction_table = (typeActions*)malloc(START_MEMORY * sizeof(typeActions));
		if (instruction_table == NULL) {
			printf("\nerror in line %d Allocation failed.\n", line);
			exit(1);
		}
	}
	else {
		instruction_table = (typeActions*)realloc(instruction_table, (START_MEMORY + numOfInstruction + 1) * sizeof(typeActions));
		if (instruction_table == NULL) {
			printf("\nerror in line %d Allocation failed.\n", line);
			exit(1);
		}
	}
}
/*Allocation method for External labels that used Conditional branching instructions*/
void allocationOfMemoryToExtenalSymbol(int line) {
	if (externSymbol++ == 0) {
		external_symbol = (externalsymboltable*)malloc(START_MEMORY * sizeof(externalsymboltable));
		if (external_symbol == NULL) {
			printf("\nerror in line:%d Allocation failed.\n", line);
			exit(1);
		}
	}
	else {
		external_symbol = (externalsymboltable*)realloc(external_symbol, (START_MEMORY + externSymbol + 1) * sizeof(externalsymboltable));
		if (external_symbol == NULL) {
			printf("\nerror in line:%d Allocation failed.\n", line);
			exit(1);
		}
	}
}
/*This method accepts the type of data to be entered and according to which it allocates the required space.
The method checks the status of the allocation counter for each type of data.
The first time the operation will allocate accordingly a maximum size of 60 cells,
 and when a reallocation is needed the operation will add another 60 places in memory.
*/
void allocationForAllTheAction(type typeVariable, int line) {
	if (typeVariable == DATA_DB) {
		if (numOfDataB % (START_MEMORY - 1) == 0 || numOfDataB == 0)
			allocationOfMemoryToDataB(line);
		else
			numOfDataB++;
	}
	else if (typeVariable == DATA_DH) {
		if (numOfDataH % (START_MEMORY - 1) == 0 || numOfDataH == 0)
			allocationOfMemoryToDataH(line);
		else
			numOfDataH++;

	}
	else if (typeVariable == DATA_DW) {
		if (numOfDataW % (START_MEMORY - 1) == 0 || numOfDataW == 0)
			allocationOfMemoryToDataW(line);
		else
			numOfDataW++;
	}
	else if (typeVariable == OTHER) {
		if (numOfInstruction % (START_MEMORY - 1) == 0 || numOfInstruction == 0)
			allocationOfMemoryToInstructionTable(line);
		else
			numOfInstruction++;
	}
	else if (typeVariable == LABEL) {
		if (numOfLabels % (START_MEMORY - 1) == 0 || numOfLabels == 0)
			allocationOfMemoryToSymbolTable(line);
		else
			numOfLabels++;
	}
	else if (typeVariable == SIGN) {
		if (sumOfCharacters % (START_MEMORY - 1) == 0 || sumOfCharacters == 0)
			allocationOfMemoryToSymbolData(line);
		else
			sumOfCharacters++;
	}
	else if (typeVariable == EXTERN) {
		if (externSymbol % (START_MEMORY - 1) == 0 || externSymbol == 0)
			allocationOfMemoryToExtenalSymbol(line);
		else
			externSymbol++;
	}
}

