#include <stdio.h>
#include <stdlib.h>


void sumArray(int *array,int *auxArray){
	for (int i = 0;i<40000;i++)
		array[i] = array[i] + auxArray[i];
}

void printArray(int *array){
	int i;
	for (i = 40000;i>0;i--)
		if (array[i]!=0)
			break;
	for (i;i>=0;i--)
		printf("%d",array[i]);
	printf("\n");
}

void copyArray (int *array, int *auxArray){//Copies array into auxArray
	for (int i = 0;i<40000;i++)
		auxArray[i] = array[i];
}

void ceilingFunction (int *array){//Grabs all numbers greater than 10 in any given array position and does a carryover operation
	for (int i = 0;i<39999;i++){//Limit is 39999 because the position i+1 will be checked occasionally
				if (array[i]>9){
					array[i+1] = array[i+1] + (array[i]/10);
					array[i] = array[i]%10;
				}
	}
}

void resetArray(int *array){
	for(int i = 0;i<40000;i++)
		array[i] = 0;//All positions are set as -1 for ease of reading the results once the operation is finished
}

void numIntoArray(int num,int numSize,int *array){//Grabs any number of size numSize, decomposes it and writes it into the array
	int i = 0;
	while (num>0){
		array[i]=num%10;
		num = num/10;
		i++;
	}
}

int sizeOfNum(int num){//Checks how big the number num is(Example : returns 3 for num = 100, returns 4 if num = 1000)
	int i = 0;
	while (num>0){
		i++;
		num = num/10;
	}
	return i;
}

void fac(int *resultVector,int *auxVector,int num){//Function that does the operation proper
	int numSize = sizeOfNum(num);
	numIntoArray(num,numSize,auxVector);
	while (num>1){
		for (int i = 0;i<num-1;i++){
			sumArray(resultVector,auxVector);
			ceilingFunction(resultVector);//Ceiling function is run after every sum
		}
		copyArray(resultVector,auxVector);
		num--;
	}
	printArray(resultVector);
}

int main(){
	int num;
	int *resultVector;
	int *auxVector;
	resultVector = (int *) malloc(40000 * sizeof(int));//Vector is 40000 positions long since the largest number this program will support is 10!, which should have around 36000 positions. Otherwise, realloc() should be used
	auxVector = (int *) malloc(40000 * sizeof(int));//Auxiliary vector will house the result of the previous operation so it can be added to the result vector
	if((resultVector==NULL)||(auxVector==NULL)){
		printf("Memory allocation failure!\n");//In case your PC can't allocate the memory, in which case the program will terminate itself
		return 0;
	}
	resetArray(resultVector);
	resetArray(auxVector);
	printf("Digite um numero inteiro: ");
	scanf("%d",&num);
	fac (resultVector,auxVector,num);
}