#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct road {
	char departureLocation[20];
	char arrivalLocation[20];
	int distance;
} road;

typedef struct stringList {//Necessary simply because C doesn't have a String type, thus making arrays of Strings not possible
	char string[20];
}stringList;

int vertexCount (road *roadList,int roadAmount){//Uses the list of roads in order to count the amount of vertices/cities in the graph
	char currentString[20];
	int vertexNum = 1;
	stringList vertexList[roadAmount];
	for (int i=0;i<roadAmount;i++)//Sets all strings to the name '----- ... -', simulating a NULL postion in the array
		for (int j = 0;i<20;i++)
			vertexList[i].string[j] = '-';
	strcpy(currentString,roadList[0].departureLocation);
	strcpy(currentString,vertexList[0]);
	for (int i = 0;i < roadAmount;i++){
		if (strcmp(currentString,roadList[0].departureLocation)!=0){
			//WIP - Code here will first compare currentString to all Strings in stringList. If there is no such String in the list, it will create one and break from the loop
		}
	}
	return vertexNum;
}

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
	char currentString[100];//Temporary storage space for strings
	fgets (currentString,100,inputFile);
	int i = 0;//Auxiliary number 01
	int j = 0;//Auxiliary number 02
	while (currentString[i] != '\\')
		i++;
	while (i>0){
		roadAmount = roadAmount + (currentString[j]-48)*pow(10,i);
		i--;
		j++;
	}
	roadAmount = roadAmount/10;//Note to self : roadAmount is the expected result times 10. I'll come back to solve it later, for now, this will have to do
	i=0;j=0;//Variables i and j are reset in the end of every block where they are needed, for the sake of posterity
	//Code responsible for reading the remainder of the lines in the input file
	road roadList[roadAmount];
	for (i=0;i<roadAmount;i++)
		roadList[i].distance = 0;
	for (i=0;i<roadAmount;i++){
		fscanf(inputFile,"%s %s %s", roadList[i].departureLocation , roadList[i].arrivalLocation , currentString);
		int aux = 0; //Aux int used to turn the String that determines distance into an int
		while (currentString[j] != '\\')
			j++;
		while (j>0){
			roadList[i].distance = roadList[i].distance + (currentString[aux]-48)*pow(10,j);
			j--;
			aux++;
		}
		roadList[i].distance = roadList[i].distance/10;//The code to turn String to int was essentially copied from above and suffers from the same issue. Note to self : might as well turn it into a function
	}

	road currentJourney;//Reads the very last line in the file
	fscanf(inputFile,"%s %s",currentJourney.departureLocation,currentJourney.arrivalLocation);
	currentJourney.distance = -1;//Sets the distance between both cities as -1

	for (i = 0 ; i<roadAmount ; i++)
		printf("%s %s %d\n",roadList[i].departureLocation,roadList[i].arrivalLocation,roadList[i].distance );
	printf("There are %d roads in this map\n",roadAmount ); //Commented code is used to prove that the program has successfully transfered all the info from the file to the struct array
	printf("We are leaving %s, going to %s, which is %dkm away from here\n",currentJourney.departureLocation,currentJourney.arrivalLocation,currentJourney.distance );
	i=0;j=0;
	fclose(inputFile);//File is no longer needed so it may be closed

	int vertex = vertexCount(roadList,roadAmount);//Amount of vertices in the graph
	printf("%d\n",vertex );
}