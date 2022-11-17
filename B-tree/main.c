#include <stdio.h>
#include <stdlib.h>

FILE *fin;
FILE *fout;

typedef	struct	BNode*	BNodePtr;
struct	BNode{
    int	order;
    int	size;			/*	number	of	children	*/
    BNodePtr *child;	/*	children pointers	*/
    int	*key;			/*	keys	*/
    int	is_leaf;
}BNode;

BNodePtr CreateTree(int	order);
void Insert(BNodePtr* root,	int	key);
int	Find(BNodePtr root,	int	key);
void PrintTree(BNodePtr root);
void DeleteTree(BNodePtr root);

void MergeTree(BNodePtr root , BNodePtr key, int order);
BNodePtr NodeSplit(BNodePtr node1, int key);
BNodePtr FindTree(BNodePtr root, int key);
void InsertHelp(BNodePtr parent, BNodePtr child, BNodePtr key,int index);
int FindIndex(BNodePtr root, int key);

int main(int argc, char *argv[]){
    fin = fopen("input.txt","r");
    fout = fopen("output.txt","w");

    int order;
    fscanf(fin,"%d",&order);
    BNodePtr root = CreateTree(order);

    char cv ;
    int key;
    while (!feof(fin)){
        fscanf(fin,"%c",&cv);
        switch (cv) {
            case 'i':
                fscanf(fin, "%d", &key);
                if (Find(root, key))
                    fprintf(fout, "insert error : key %d is already in the tree!\n", key);
                else
                    Insert(&root, key);
                break;
            case 'f':
                fscanf(fin, "%d", &key);
                if (Find(root, key))
                    fprintf(fout, "key %d found\n", key);
                else
                    fprintf(fout, "finding error: key %d is not in the tree!\n", key);
                break;
            case 'p':
                if (root->size == 1)
                    fprintf(fout, "print error: tree is empty!");
                else
                    PrintTree(root);
                fprintf(fout, "\n");
                break;

        }
    }

    fclose(fin);
    fclose(fout);

    return 0;
}

BNodePtr CreateTree(int order){
    BNodePtr new = (BNodePtr) malloc(sizeof(struct BNode));
    new->order = order;
    new->size = 0;
    new->child = NULL;
    new->key = (int*) malloc(sizeof(int)*(order-1));
    new->is_leaf = 1;
}

void Insert(BNodePtr *root, int key){
    BNodePtr new = (BNodePtr) malloc(sizeof(struct BNode));
    InsertHelp(*root,(*root)->child[FindIndex(*root,key)],new,NULL);
}

void InsertHelp(BNodePtr parent, BNodePtr child, BNodePtr key, int index){
    if (key == NULL)
        return;
    if(child->is_leaf == 0){
        int idx = FindIndex(child,key->key[0]);
        InsertHelp(child, child->child[index],key,idx);
    }
    MergeTree(child,key,index);
}

void MergeTree(BNodePtr root, BNodePtr key, int index){
    if(root->size == root->order -1){
        BNodePtr new = (BNodePtr) malloc(sizeof(struct BNode));

        return;
    }
    else{
        for(int i = root->size; i > index; i--){
            root->key[i] = root->key[i-1];
        }
        root->key[index] = key->key[0];
        for(int i = root->size + 1; i > index + 1; i--){
            root->child[i] = root->child[i-1];
        }
        root->child[index] = key->child[0];
        root->child[index+1] = key->child[1];
    }

}

int Find(BNodePtr root, int key){
    for(int n = 0; n < root->size; n++)
        if (root->key[n] == key)
            return 1;
    if(root->is_leaf)
        return 0;
    for(int n = 0; n < root->size; n++)
        if (root->key[n] > key) {
            Find(root->child[n], key);
            break;
        }
    Find(root->child[root->size],key);
}

BNodePtr FindTree(BNodePtr root, int key){
    if(root->is_leaf)
        return root;
    for(int n = 0; n < root->size; n++)
        if (root->key[n] > key)
            Find(root->child[n], key);
    Find(root->child[root->size],key);
    //FindTree(root->child[FindIndex(root,key)],key);
}

void PrintTree(BNodePtr root) {
    for (int i = 0; i < root->size + 1; i++) {
        if (root->is_leaf == 1) {
            for (int j = 0; j < root->size; j++) {
                fprintf(fout, "%d ", root->key[j]);
            }
            break;
        }
        else {
            PrintTree(root->child[i]);
            fprintf(fout, "%d ", root->key[i]);
        }
    }
}

int FindIndex(BNodePtr root, int key){
    for(int n = 0; n < root->size; n++)
        if (root->key[n] > key) {
            return n;
        }
    return root->size;
}