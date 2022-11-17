#include <stdio.h>
#include <stdlib.h>

FILE *fin;
FILE *fout;

typedef struct ThreadedTree* ThreadedPtr;
typedef int ElementType;

struct ThreadedTree{
    int left_thread;
    int right_thread;
    ThreadedPtr left_child;
    ElementType data;
    ThreadedPtr right_child;
};

ThreadedPtr CreateTree();
int Insert(ThreadedPtr root, int root_idx,ElementType data, int idx);
void printInorder(ThreadedPtr root);

int main(int argc, char  *argv[]){
    fin = fopen("input.txt","r");

    ThreadedPtr root = CreateTree();

    int NUM_NODES;
    fscanf(fin,"%d",&NUM_NODES);

    int root_idx =0, idx = 0;

    while (++idx <= NUM_NODES){
        ElementType data;
        fscanf(fin,"%d",&data);

        if (Insert(root,root_idx,data,idx)==0){
            return 0;
        }
    }
    printInorder(root);
}

ThreadedPtr CreateTree(){
    ThreadedPtr tree = NULL;
    tree =(ThreadedPtr)malloc(sizeof(struct ThreadedTree));
    if(tree == NULL){
        printf("Out of space!\n");
        return NULL;
    }
    tree->data = -1;
    tree->left_thread = 1;
    tree->left_child = tree;
    tree->right_thread = 1;
    tree->right_child = tree;
    return tree;
}

void printInorder(ThreadedPtr root){
    while (root->left_child->data == -1)
        root = root -> left_child;
    while (root->right_child->data == -1) {
        printf("%d", root->data);
        root = root->right_child;
    }
}
void reverseArrayInt(int* array, int size) {
    int temp;

    for (int i = 0; i < size / 2; i++) {
        temp = array[i];
        array[i] = array[(size - 1) - i];
        array[(size - 1) - i] = temp;
    }
}

int* ten_to_two(unsigned n) {
    // 동적 배열 생성
    int size = 1;
    int *a = (int *) malloc(sizeof(int) * size);
    // 배열에 원소 넣기 ex) 11 => 1 1 0 1 (2로 나누고 나머지 값)
    for (int i = 0; n != 0; i++) {
        a[i] = n % 2;
        n /= 2;
        if (n != 0) {
            size++;
            a = realloc(a, sizeof(int) * size);
        }
    }
    reverseArrayInt(a,size);
    return a;
}
int Insert(ThreadedPtr root, int root_idx, ElementType data, int idx){
    int* a = ten_to_two(idx);

    for(int i = 0; i<sizeof (*a)/sizeof (int); i++){
        if(i == sizeof(*a)/ sizeof(int)-1){
            ThreadedPtr node = (ThreadedPtr)malloc(sizeof(struct ThreadedTree));
            node->data = data;

            if(a[i])
                root = root->right_child;
            else
                root = root->left_child;
        }
        if(a[i])
            root = root->right_child;
        else
            root = root->left_child;

    }
}