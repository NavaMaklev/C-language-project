
#include "project.h"
void writef(char name[])
{	
        FILE *fdob,*fdex,*fden;
        bitToPrint keepFourBytes;
	bitToPrintH keepTowBytes;
	int i,j,db, dh, dw,temp,address;
        char nameob[MAX_FILE_NAME];
	char nameen[MAX_FILE_NAME];
	char nameex[MAX_FILE_NAME];
	j = 0;
	db = 0;
	dw = 0;
	dh = 0;
        keepFourBytes.bits = 255;
        keepTowBytes.bits = 255;
        fdob=fdex= fden= NULL;
	address = 100;
	strcpy(nameob, name);
	strcat(nameob, ".ob");
	strcpy(nameex, name);
	strcat(nameex, ".ext");
	strcpy(nameen, name);
	strcat(nameen, ".ent");
	fdob = fopen(nameob, "w");
	if (externSymbol != 0){
		fdex = fopen(nameex, "w");
               for(i=0;i<externSymbol;i++)
               fprintf(fdex,"%s %04d\n",external_symbol[i].labelName,external_symbol[i].address);     
         fclose(fdex);
        }
	if (entrySymbol != 0){
		fden = fopen(nameen, "w");
                for(i=0;i<numOfLabels;i++){
                if(symbol_table[i].entry==TRUE)
                   fprintf(fden,"%s %04d\n",symbol_table[i].symbol,symbol_table[i].value);
                }
        fclose(fden);
        }
	fprintf(fdob,"%5d %d\n", ICF - 100, DCF);
	for (i = 0; i < numOfInstruction; i++) {
		fprintf(fdob,"%04d  ", address);
		address += 4;
		for (j = 0; j < 4; j++) {
			fprintf(fdob,"%02X ",keepFourBytes.bits & instruction_table[i].print.bits);
                        instruction_table[i].print.bits>>=8;
		}
		fprintf(fdob,"\n");
	}
        j=0;
	fprintf(fdob,"%04d  ", address);
	address += 4;
	for (i = 0;i < sumOfCharacters;i++) {
		if (symbolData[i] == 'b' || symbolData[i] == 'a') {
			if (j == 4) {
				fprintf(fdob,"\n");
				fprintf(fdob,"%04d  ", address);
				address += 4;
				j = 0;
			}
			fprintf(fdob,"%02X ",keepTowBytes.bits&dataB[db].numOfBits);
			db++;
			j++;
		}
		else if (symbolData[i] == 'h') {
			for (temp = 0;temp < 2;temp++) {
				if (j == 4) {
					fprintf(fdob,"\n");
					fprintf(fdob,"%04d  ", address);
					address += 4;
					j = 0;
				}
				fprintf(fdob,"%02X ", keepTowBytes.bits&dataH[dh].numOfBits);
                                dataH[dh].numOfBits>>=8;
				j++;
			}
			dh++;
		}
		else if (symbolData[i] == 'w') {
			for (temp = 0;temp < 4;temp++) {
				if (j == 4) {
					fprintf(fdob,"\n");
					j = 0;
					fprintf(fdob,"%04d  ", address);
					address += 4;
				}
				fprintf(fdob,"%02X ", keepFourBytes.bits&dataW[dw].numOfBits);
                                dataW[dw].numOfBits>>=8;
				j++;
			}
			dw++;
		}
	}
fclose(fdob);
}
