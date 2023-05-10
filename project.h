
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#define MEMORY_ADRRES 100
#define START_MEMORY 60
#define MAX_LINE 80 /* maximum chars per line */
#define MAX_LABEL 31 /* maximum number of labels */
#define SIZE_OF_WORD 4
#define SIZE_OF_HALF_WORD 2
#define MAX_FILE_NAME 30
#define SIZE_OF_BYTE 1
typedef enum { FALSE, TRUE } boolean;
/*Action instruction structure*/
typedef struct {
	char methodName[6];
	char methodType;
	int funct;
	int opcode;
	int help;
}action;
/* help=
Auxiliary variable for identifying the types of operations.
For type R operations the variable is used for the correct amount of registers.
For type I operations the variable will contain 1,2,3 depending on the type of instruction.
1-Arithmetic and logical instructions
2- Conditional branching instructions
3-Instructions for loading and storing in memory
For type J operations:
0 per action 'stop' (no registers)
1 for actions: 'la','call' (one register)
2 per action 'jmp'(2 registers)
 */
 /*external symbol table*/
typedef struct {
	unsigned int address;
	char labelName[MAX_LABEL];
}externalsymboltable;
/*R typeAction*/
typedef struct {
	unsigned int notUsing : 6;
	unsigned int funct : 5;
	unsigned int rd : 5;
	unsigned int rt : 5;
	unsigned int rs : 5;
	unsigned int opcode : 6;
	unsigned int address;
}R;
/*I typeAction*/
typedef struct {
	unsigned int immed : 16;
	unsigned int rt : 5;
	unsigned int rs : 5;
	unsigned int opcode : 6;
	unsigned int address;
}I;
/*J typeAction*/
typedef struct {
	unsigned int address : 25;
	unsigned int reg : 1;
	unsigned int opcode : 6;
	unsigned int addressIC;
}J;
typedef struct {
	int numOfBits : 8;
	int address;
}db;
typedef struct {
	int numOfBits : 32;
	int address;
}dw;
typedef struct {
	int numOfBits : 16;
	int address;
}dh;
/*This structure contains 32 bits for 4-bit prints.
When printing, we will turn on the 8 right-hand bits and so on by operation,
and we will also print the input that we saved in the data structures.*/
typedef struct {
	int bits : 32;
}bitToPrint;
/*This structure contains 16 bits for 2-byte prints.
When printing, we will turn on the 8 right-hand bits and so on by operation,
and we will also print the input that we saved in the data structures.*/
typedef struct {
	int bits : 16;
}bitToPrintH;
typedef union {
	R rAction;
	I iAction;
	J jAction;
	bitToPrint print;
}typeActions;
/*labelStructure*/
typedef struct {
	char symbol[MAX_LABEL];
	int value;
	char attributes[10];
	boolean entry;
}label;
typedef enum {
	LABEL, DATA_DB, DATA_DH, DATA_DW, DATA_ASCIZ, EXTERN, ENTRY, END, NOTE, OTHER, SIGN
}type; /*
LABEL = a label - symbol
DATA_DW= data in size of word
DATA_DB = data in size of byte
DATA_DH = data in size of half-word
DATA_ASCIZ= string data
EXTERN = .extern
ENTRY = .entry
END = empty line
NOTE = note
SIGN='b'\'h'\'w'\'a'
OTHER = non of the above */
boolean stage1(FILE* file);
void updateAdress();
char* legalsymbol(char* start, boolean isEntry, boolean pass2, int line);
type typeWord(char* start, int* h, int line);
boolean islabel(char word[], int line);
boolean enterInTable(char* name, int address, boolean isExternal, char* type, int line);
char* getlable(char start[], int* j);
boolean notintable(int* num, char namel[]);
boolean lineOfData(char* current, type typeData, int line);
void enterData(type dataType, int number, int line);
void allocationOfMemoryToDataB(int line);
void allocationOfMemoryToDataH(int line);
void allocationOfMemoryToDataW(int line);
void allocationOfMemoryToSymbolData(int line);
void allocationOfMemoryToExtenalSymbol(int line);
boolean lineOfCode(char* current, int numberOfLine);
boolean checkLineOfR(char* current, int index, int numberOfLine);
boolean checkLineOfI(char* current, int index, int numberOfLine);
boolean checkLineOfJ(char* current, int index, int numberOfLine);
void allocationOfMemoryToInstructionTable(int line);
boolean stage2(FILE* fd2);
boolean lineOfCode2(char* current, int line);
boolean checkLineOfI2(char* current, int indexAction, int line);
boolean checkLineOfJ2(char* current, int indexAction, int line);
boolean checkEntryOrExternLine(char* current, boolean isEntry, int line, int lengthLabel);
void allocationForAllTheAction(type typeVariable, int line);
void allocationOfMemoryToSymbolTable(int line);
void writef(char name[]);
extern label* symbol_table;
extern int numOfLabels;
extern db* dataB;
extern dh* dataH;
extern dw* dataW;
extern char* symbolData;
extern int numOfDataB;
extern int numOfDataH;
extern int numOfDataW;
extern int sumOfCharacters;
extern int externSymbol;
extern int entrySymbol;
extern typeActions* instruction_table;
extern int numOfInstruction;
extern externalsymboltable* external_symbol;
extern int  IC, DC, ICF, DCF, IC2;
extern action allActions[27];








