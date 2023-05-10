#include "project.h"

/*The purpose of the project is to translate assembly files into octal / binary files which
Are used in the assembly linking program.
Input files are given in command arguments ie maman14 ps cs a rs
The program will attach.as to the file names for input.
If a translation encounters an error the program will print to the standard input the errorand the line number in which the error occurred.
If there are no errors it will generate 3 files for each input file :
1) file.ob - object code
2) file.ent - record label codes
3) file.ext - External label codes
Project implementation :
The set of instructions - The set of instructions is a dynamic data structure of the Union type which contains within it the 3 different types of instructions which each instruction is implemented within its own unique structure(assigned by bit fields)
The data set - divided into 3 different types of dynamic structures :
dataB - for data in one byte size.
dataH - for 2 byte data.
dataW - for 4 - byte data.
There is also an array of external labels and table of symbols that is implemented using a dynamic data structure.

this array including all the actions*/
action allActions[27] =
{
{"add",'R',1,0,3},
{"sub",'R',2,0,3},
{"and",'R',3,0,3},
{"or",'R',4,0,3},
{"nor",'R',5,0,3},
{"move",'R',1,1,2},
{"mvhi",'R',2,1,2},
{"mvlo",'R',3,1,2},
{"addi",'I',0,10,1},
{"subi",'I',0,11,1},
{"andi",'I',0,12,1},
{"ori",'I',0,13,1},
{"nori",'I',0,14,1},
{"bne",'I',0,15,2},
{"beq",'I',0,16,2},
{"blt",'I',0,17,2},
{"bgt",'I',0,18,2},
{"lb",'I',0,19,3},
{"sb",'I',0,20,3},
{"lw",'I',0,21,3},
{"sw",'I',0,22,3},
{"lh",'I',0,23,3},
{"sh",'I',0,24,3},
{"jmp",'J',0,30,2},
{"la",'J',0,31,1},
{"call",'J',0,32,1},
{"stop",'J',0,63,0}
};
int IC, DC, ICF, DCF, IC2;
int numOfInstruction;
int entrySymbol;
int externSymbol;
int sumOfCharacters;
int sumOfCharacters;
int numOfDataW;
int numOfDataH;
int numOfDataB;
int numOfLabels;
char* symbolData;
dw* dataW;
dh* dataH;
db* dataB;
label* symbol_table;
externalsymboltable* external_symbol;
typeActions* instruction_table;
int main(int argc, char** argv) {
	FILE* fd;
	boolean error;
	char name[MAX_FILE_NAME];
	char nameFile[MAX_FILE_NAME];
	if (argc == 1) {
		printf("\nYou did not enter a file name.\n");
	}
	while (--argc) {
		DC = 0;
		IC = MEMORY_ADRRES;
		IC2 = MEMORY_ADRRES;
		ICF = 0;
		DCF = 0;
		entrySymbol = 0;
		externSymbol = 0;
		sumOfCharacters = 0;
		numOfLabels = 0;
		numOfDataW = 0;
		numOfDataH = 0;
		numOfDataB = 0;
		numOfInstruction = 0;
		strcpy(name, argv[argc]);
		strcpy(nameFile, name);
		strcat(nameFile, ".as");
		fd = fopen(nameFile, "r");
		if (fd == NULL)
			printf("\nThe file\"%s\"does not exist.\n", nameFile);
		else {
			error = stage1(fd);
			if (error == TRUE) {
				printf("\nerror exist in file %s\n", name);
				exit(1);
			}
			else {
				rewind(fd);
				error = stage2(fd);
				if (error == TRUE) {
					printf("\nerror exist in file %s\n", name);
					exit(1);
				}
				else {
					writef(name);
				}
			}
		}
		free(dataB);
		free(dataH);
		free(dataW);
		free(symbolData);
		free(symbol_table);
		free(external_symbol);
		free(instruction_table);
		fclose(fd);
	}
	return 0;

}

