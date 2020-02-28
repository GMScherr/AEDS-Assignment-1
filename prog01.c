#include <stdio.h>
#include <math.h>

typedef struct road {
	char departureLocation[20];
	char arrivalLocation[20];
	int distance;
} road;

int main(){
	//File opening
	char fileName[20];
	FILE *inputFile;
	printf("Digite o nome do arquivo de entrada: ");
	scanf("%s",fileName);
	inputFile = fopen(fileName,"r");
	if (!inputFile){
		printf("Specified file does not exist\n.");
		return 0;
	}
	//Code necessary to read the very first line of the input file. At the time of writing all this code I had no idea it could be done with a simple fscanf. Bollocks
	int roadAmount = 0;
	char currentString[100];
	fgets (currentString,100,inputFile);
	int i = 0;//Auxiliary number 01
	int j = 0;//Auxiliary number 02
	while (currentString[i] != '\\')
		i++;
	printf("%d\n",i);
	while (i>0){
		roadAmount = roadAmount + (currentString[j]-48)*pow(10,i);
		i--;
		j++;
	}
	roadAmount = roadAmount/10;//Note to self : roadAmount is the expected result times 10. I'll come back to solve it later, for now, this will have to do
	i=0;j=0;//Variables i and j are reset in the end of every block where they are needed, for the sake of posterity
	//Code responsible for reading the remainder of the lines in the input file
	road roadList[roadAmount];
	for (i=0;i<roadAmount;i++){
		fgets (currentString,100,inputFile);
	}

	fclose(inputFile);
}