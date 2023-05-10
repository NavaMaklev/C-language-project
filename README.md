# C-language-project
C language assembler implementation
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
