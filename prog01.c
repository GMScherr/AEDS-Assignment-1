#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define INFINITE 9999
#define MAX 10

//So far : code does not work. When passing the adjecencyMatrix to dijkstra();, the values of the variables change wildly.
//Simply running this code will show that the adjacency matrix printed by main() and dijkstra() are different, despite no apparent reason.
//An example of the phenomenom cited above can be found in this image : https://imgur.com/a/BjX1OOo

typedef struct road {
    char departureLocation[20];
    char arrivalLocation[20];
    int distance;
} road;

typedef struct stringList {
    char string[20];
} stringList;

void dijkstra(int G[MAX][MAX],int n,int startnode);

/*int **Aloca_matriz(int lin, int col){//Original code from : https://github.com/PierreVieira/AEDS_I_C/blob/master/Distancia%20entre%20duas%20cidades.c
    int **matriz;
    matriz = malloc(sizeof(int*)*lin);
    for (int i = 0; i < lin; ++i) {
        matriz[i] = malloc(sizeof(int)*col);
    }
    return matriz;
}*/

int fetchDistance(stringList *vertexList,road *roadList,int roadAmount,int i,int j){//Fetches the distance in between the cities indicated by the index of i and j
    int returnValue;
    char departureString[20];
    char arrivalString[20];
    strcpy(departureString,vertexList[i].string);
    strcpy(arrivalString,vertexList[j].string);
    for (int i = 0;i<roadAmount;i++)
        if (((strcmp(arrivalString,roadList[i].arrivalLocation)==0)&&(strcmp(departureString,roadList[i].departureLocation)==0))||((strcmp(arrivalString,roadList[i].departureLocation)==0)&&(strcmp(departureString,roadList[i].arrivalLocation)==0))){
            returnValue = roadList[i].distance;
            break;
        }
    return returnValue;
}

int stringSearch (stringList *vertexList,char *currentString,int vertex){//Returns 1 if vertexList does not contain currentString
    int returnNum = 1;
    for (int i = 0;i<vertex;i++){
        if (strcmp(vertexList[i].string,currentString)==0)
            returnNum = 0;
    }
    return returnNum;
}

void vertexListSet(stringList *vertexList , road *roadList , int vertex , int roadAmount ){
    char departureString[20];
    char arrivalString[20];
    int vertexListIndex = 0;
    for (int i = 0;i<20;i++){
        departureString[i] = roadList[0].departureLocation[i];
        arrivalString[i] = roadList[0].arrivalLocation[i];
    }
    for (int i = 0;i<roadAmount;i++){
        if(stringSearch(vertexList,departureString,vertex)){
            strcpy(vertexList[vertexListIndex].string,departureString);
            vertexListIndex++;
        }
        if(stringSearch(vertexList,arrivalString,vertex)){
            strcpy(vertexList[vertexListIndex].string,arrivalString);
            vertexListIndex++;
        }
        strcpy(departureString,roadList[i].departureLocation);
        strcpy(arrivalString,roadList[i].arrivalLocation);
    }
}

int vertexCount (road *roadList,int roadAmount){//Uses the list of roads in order to count the amount of vertices/cities in the graph
    char currentString[20];
    int vertexNum = 1;
    for (int i = 0;i<20;i++)
        currentString[i]=roadList[0].departureLocation[i];//Copies the first city in the list into currentString
    for (int i = 0;i<roadAmount;i++)
        if (strcmp(roadList[i].departureLocation,currentString) != 0){//If the name of the departure location is different fromt the current name, a new city name has been found
            vertexNum++;                                              //Note : this only works because of how the input file is structured, this is *not* a proper sorter and counter
            for (int j = 0;j<20;j++)
                currentString[j]=roadList[i].departureLocation[j];//Copying Strings manually because this won't work with strcpy for some reason
        }
    vertexNum++;
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
    int i = 0;//Auxiliary number 01
    int j = 0;//Auxiliary number 02
    fscanf(inputFile,"%s",currentString);
    for (i = 0;i<20;i++)
        if (currentString[i]>56||currentString[i]<48)
            break;
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
        for (j = 0;j<20;j++)
            if (currentString[j]>56||currentString[j]<48)
                break;
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
    printf("There are %d cities in the map\n",vertex );

    int adjacencyMatrix [vertex][vertex];

    //int **adjacencyMatrix;
    //adjacencyMatrix = Aloca_matriz(vertex,vertex); //An attempt has been made to salvage this code from Pierre's example (Code available at https://github.com/PierreVieira/AEDS_I_C/blob/master/Distancia%20entre%20duas%20cidades.c)
                                                     //Unfortunately very much unsuccessful
    stringList vertexList[vertex];
    for (i=0;i<vertex;i++)
        for (j=0;j<20;j++)
            vertexList[i].string[j] = '-';//Sets vertexList to "--------------------", as if it were a null String
    vertexListSet(vertexList,roadList,vertex,roadAmount);

    for (i = 0;i<vertex;i++)
        printf("%s\n",vertexList[i].string);

    for (i = 0;i<vertex;i++){
        for (j = 0;j<vertex;j++){
            if (j == i)
                adjacencyMatrix[i][j]=0;
            else
                adjacencyMatrix[i][j]=fetchDistance(vertexList,roadList,roadAmount,i,j);
        }
    }

    for (i = 0;i<vertex;i++){
        for (j = 0;j<vertex;j++){
            printf("%d ",adjacencyMatrix[i][j]);
        }
        printf("\n");
    }

    for (i = 0;i<vertex;i++)
        if (strcmp(currentJourney.departureLocation,vertexList[i].string)==0)
            break;
    printf("%d\n",i);

    dijkstra(adjacencyMatrix,vertex,i);
}

void dijkstra(int G[MAX][MAX],int n,int startnode)//Code from https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
                                                  //Note : the code does not work as is, for no apparent reason (So far).
{
    
        for (int i = 0;i<n;i++){
        for ( int j = 0;j<n;j++){
            printf("%d ",G[i][j]);
        }
        printf("\n");
    }

    int cost[MAX][MAX],distance[MAX],pred[MAX];
    int visited[MAX],count,mindistance,nextnode,i,j;
    
    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far
    //create the cost matrix
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(G[i][j]==0)
                cost[i][j]=INFINITE;
            else
                cost[i][j]=G[i][j];
    
    //initialize pred[],distance[] and visited[]
    for(i=0;i<n;i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }
    
    distance[startnode]=0;
    visited[startnode]=1;
    count=1;
    
    while(count<n-1)
    {
        mindistance=INFINITE;
        
        //nextnode gives the node at minimum distance
        for(i=0;i<n;i++)
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }
            
            //check if a better path exists through nextnode            
            visited[nextnode]=1;
            for(i=0;i<n;i++)
                if(!visited[i])
                    if(mindistance+cost[nextnode][i]<distance[i])
                    {
                        distance[i]=mindistance+cost[nextnode][i];
                        pred[i]=nextnode;
                    }
        count++;
    }
 
    //print the path and distance of each node
    for(i=0;i<n;i++)
        if(i!=startnode)
        {
            printf("\nDistance of node%d=%d",i,distance[i]);
            printf("\nPath=%d",i);
            
            j=i;
            do
            {
                j=pred[j];
                printf("<-%d",j);
            }while(j!=startnode);
    }
}