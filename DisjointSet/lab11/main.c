#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct  _DisjointSet{
    int size;
    int *ptr_arr;
}DisjointSets;

typedef struct  _PrintDisjointSet{
    int size;
    int *ptr_arr;
}PrintDisjointSets;

FILE *fout;
void init(DisjointSets *sets,DisjointSets *maze_print,int num);
void Union(DisjointSets *sets,int i,int j);
int find(DisjointSets *sets, int i);
void createMaze(DisjointSets *sets, DisjointSets *maze_print,int num);
void printMaze(DisjointSets *sets, int num);
void freeMaze(DisjointSets *sets,DisjointSets *maze_print);

int main(int argc, char* argv[]){
    srand((unsigned int)time(NULL));

    int num;
    FILE *fi = fopen("input.txt","r");
    fscanf(fi,"%d",&num);
    fclose(fi);

    fout = fopen("output.txt","w");

    DisjointSets *sets = (DisjointSets*) malloc(sizeof (DisjointSets));
    DisjointSets *maze = (DisjointSets*) malloc(sizeof (DisjointSets));

    init(sets,maze,num);

    createMaze(sets,maze,num);
    printMaze(maze,num);

    fclose(fout);

    return 0;
}

void init(DisjointSets* sets, DisjointSets* maze, int num){
    sets->size = num*num;
    sets->ptr_arr = malloc(sizeof (int)*sets->size+1);
    for(int i = 1; i <= sets->size; i++)
        sets->ptr_arr[i] = 0;
    maze->size = num*num*2;
    maze->ptr_arr = malloc(sizeof (int)*maze->size);
    for(int i = 1; i <= maze->size; i++)
        maze->ptr_arr[i] = 1;
    maze->ptr_arr[maze->size-1] = 0;
}

int find(DisjointSets* sets, int i){
    /*while (sets->ptr_arr[i]<0)
        i = sets->ptr_arr[i];
    return i;*/
    if (sets->ptr_arr[i] <= 0)
        return i;
    return find(sets,sets->ptr_arr[i]);
}

void Union(DisjointSets* sets, int i, int j){
    int a,b;
    a = find(sets,i);
    b = find(sets,j);
    if (a == b)
        printf("Union err");
    if (sets->ptr_arr[a] < sets->ptr_arr[b]){
        sets->ptr_arr[b] = a;
    }
    else{
        if(sets->ptr_arr[b] == sets->ptr_arr[a])
            sets->ptr_arr[a]--;
        sets->ptr_arr[b] = a;
    }
}

void createMaze(DisjointSets* sets, DisjointSets* maze, int num){
    int i;
    while (find(sets,1) != find(sets, sets->size)) {
        i = rand() % (sets->size - 1)+1;
        if (i % num != 0){
            if (find(sets,i) == find(sets,i+1))
                continue;
            Union(sets,i ,i+1);
            maze->ptr_arr[i*2-1] = 0;
        }
        if ( i + num <= sets->size){
            if (find(sets,i) == find(sets,i+num))
                continue;
            Union(sets,i,i+num);
            maze->ptr_arr[i*2] = 0;
        }
        /*if (find(sets,i), find(sets,i+num))
            continue;
        Union(sets,i,i+num);
        maze->ptr_arr[i*2] = 0;
        if (find(sets,i), find(sets,i+1))
            continue;
        Union(sets,i ,i+1);
        maze->ptr_arr[i*2-1] = 0;*/
    }
    for(i = 1; i <sets->size -1; i++ ){
        if (i % num != 0){
            if (find(sets,i) == find(sets,i+1))
                continue;
            Union(sets,i ,i+1);
            maze->ptr_arr[i*2-1] = 0;
        }
        if ( i + num <= sets->size){
            if (find(sets,i) == find(sets,i+num))
                continue;
            Union(sets,i,i+num);
            maze->ptr_arr[i*2] = 0;
        }
    }
}

void printMaze(DisjointSets *maze_print, int num) {
    int n;
    int k;
    fprintf(fout,"+");
    for(n=0; n < num; n++)
        fprintf(fout,"---+");
    for (n=1; n < maze_print->size; n+=num*2){
        if (n == 1)
            fprintf(fout,"\n ");
        else
            fprintf(fout,"\n|");
        for(k = n; k < n+num*2; k +=2){
            if(maze_print->ptr_arr[k] == 0)
                fprintf(fout,"    ");
            else
                fprintf(fout,"   |");
        }
        fprintf(fout,"\n+");
        for(k = n+1; k < n+num*2; k +=2){
            if(maze_print->ptr_arr[k] == 0)
                fprintf(fout,"   +");
            else
                fprintf(fout,"---+");
        }

    }
}