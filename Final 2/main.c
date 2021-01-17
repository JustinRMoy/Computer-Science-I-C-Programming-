/*COP 3502C FinaltermAssignment 2This program is written by:Justin Moy*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30

typedef struct tree{

    char* data;
    struct tree* left;
    struct tree* right;

}node;

node* create(char n[]){

    node* temp;
    temp = (node*)malloc(sizeof(node));
    temp->data = (char*)malloc(SIZE * sizeof(char));
    strcpy(temp->data, n);
    temp->left = NULL;
    temp->right = NULL;

    return temp;

}

node* insert(node* root, node* tmp){

    if(root == NULL)
        return tmp;
    else{

        if(strcmp(tmp->data, root->data) > 0){
            if(root->right == NULL)
                root->right = tmp;
            else
                insert(root->right, tmp);
        }else{
            if(root->left == NULL)
                root->left = tmp;
            else
                insert(root->left, tmp);
        }
        return root;
    }
}

int totalCharacters(node*  root){

    if(root == NULL)
        return 0;
    return strlen(root->data) + totalCharacters(root->left) + totalCharacters(root->right);

}

int height(node* root){

    if(root == NULL || (root->left == NULL && root->right == NULL)) return 0;

    if(height(root->left) > height(root->right))
        return 1 + height(root->left);
    return 1 + height(root->right);

}

int isBalanced(node*  root){

    if(height(root->left) == height(root->right)) return 1;
    return 0;

}

void preorder(node* root, FILE* out){

    if(root != NULL){
        fprintf(out, "%s ", root->data);
        preorder(root->left, out);
        preorder(root->right, out);
    }

}

void inorder(node* root, FILE* out){

    if(root != NULL){
        inorder(root->left, out);
        fprintf(out, "%s ", root->data);
        inorder(root->right, out);
    }

}

void postorder(node* root, FILE* out){

    if(root != NULL){
        postorder(root->left, out);
        postorder(root->right, out);
        fprintf(out, "%s ", root->data);
    }

}

int search(node* root, char searchKey[]){

    if(root == NULL) return 0;

    if(strcmp(root->data, searchKey) == 0)
        return 1;
    if(strcmp(searchKey, root->data) < 0)
        return search(root->left, searchKey);
    return search(root->right, searchKey);

}

int CountBefore(node*  root,  char searchKey[]){

    if(root != NULL){
        if(strcmp(root->data, searchKey) < 0)
            return 1 + CountBefore(root->left, searchKey) + CountBefore(root->right, searchKey);
        if(strcmp(root->data, searchKey) == 0 || strcmp(root->data, searchKey) > 0)
            return CountBefore(root->left, searchKey);
    }
    return 0;
}

int isLeaf(node* root){
    return (root->left == NULL && root->right == NULL);
}

node* parent(node* root, node* searchKey){

if(root != NULL && root != searchKey){
    if(root->left== searchKey ||root->right == searchKey)
        return root;
    if(strcmp(root->data, searchKey->data) > 0)
        return parent(root->left, searchKey);
    if(strcmp(root->data, searchKey->data) < 0)
            return parent(root->right, searchKey);
}
return NULL;
}

node* findNode(node* root, char* searchVal){

    if(root != NULL){
        if(strcmp(root->data, searchVal) == 0)
            return root;
        if(strcmp(root->data, searchVal) > 0)
            return findNode(root->left, searchVal);
        return findNode(root->right, searchVal);
    }
    return NULL;

}

node* minVal(node* root){

    if(root == NULL) return NULL;
    if(root->left == NULL) return root;
    return minVal(root->left);
}

node* maxVal(node* root){
    if(root == NULL) return NULL;
    if(root->right == NULL) return root;
    return maxVal(root->right);
}

int hasOnlyLeftChild(node* root){
    if(root->left != NULL && root->right == NULL) return 1;
    return 0;
}

int hasOnlyRightChild(node* root){
    if(root->left == NULL && root->right != NULL) return 1;
    return 0;
}

node* deleteNode(node* root, char* searchVal){

    node* delNode = findNode(root, searchVal);
    node* temp, *parentNode;
    if(delNode != NULL){
        parentNode = parent(root, delNode);

        if(isLeaf(delNode)){

            free(delNode);
            if(parentNode != NULL){
               if(strcmp(parentNode->data,  searchVal) > 0){
                    parentNode->left = NULL;
               }else{
                    parentNode->right = NULL;
               }
               return root;
            }
            return NULL;
        }

        if(hasOnlyLeftChild(delNode)){

            if(parentNode != NULL){
                if(strcmp(delNode->data, parentNode->data) < 0){
                    parentNode->left = parentNode->left->left;
                    free(delNode);
                    return root;
                }
                parentNode->right = parentNode->right->left;
                free(delNode);
                return root;
            }
            temp = delNode->left;
            free(delNode);
            return temp;
        }

        if(hasOnlyRightChild(delNode)){
            if(parentNode != NULL){
                if(strcmp(delNode->data, parentNode->data) < 0){
                    parentNode->left = parentNode->left->right;
                    free(delNode);
                    return root;
                }
                parentNode->right = parentNode->right->right;
                free(delNode);
                return root;
            }
            temp = delNode->right;
            free(delNode);
            return temp;
        }

        temp = maxVal(delNode->left);
        char *save = (char*)malloc(SIZE * sizeof(char));
        strcpy(save, temp->data);
        root = deleteNode(root, temp->data);
        strcpy(delNode->data, save);
        free(save);
        return root;
    }
    return root;
}
int main()
{
    node *root = NULL, *tmp;
    FILE *in, *out;

    in = fopen("in.txt", "r");

    int N, S, D;

    fscanf(in, "%d", &N);
    fscanf(in, "%d", &S);
    fscanf(in, "%d", &D);
    char* name = malloc(SIZE * sizeof(char));

    for(int i = 0; i < N; i++){
        fscanf(in, "%s", name);
        tmp = create(name);
        root = insert(root, tmp);
    }

    out = fopen("out.txt", "w");

    fprintf(out, "Preorder: ");
    preorder(root, out);
    fprintf(out, "\nInorder: ");
    inorder(root, out);
    fprintf(out, "\nPostorder: ");
    postorder(root, out);
    fprintf(out, "\nTotal Characters: %d\n", totalCharacters(root));

    int l =height(root->left), r = height(root->right);
    fprintf(out, "Height Left = %d, Height Right = %d. ", l, r);
    if(isBalanced(root)){
        fprintf(out, "Tree is Balanced.\n");
    }else{
        fprintf(out, "Tree is imbalanced.\n");
    }

    fprintf(out, "Search Phase:\n");
    char *searchKey = malloc(SIZE * sizeof(char));
    for(int i = 0; i < S; i++){
        fscanf(in, "%s", searchKey);
        fprintf(out, "%s: ", searchKey);
        if(search(root, searchKey)){
            fprintf(out, "Found, ");
            fprintf(out, "Items before: %d\n", CountBefore(root, searchKey));
        }else{
            fprintf(out, "Not Found, Items before: 0\n");
        }
    }

    fprintf(out, "Delete Phase:\n");
    for(int i = 0; i < D; i++){
        fscanf(in, "%s", searchKey);
        root = deleteNode(root, searchKey);
        fprintf(out, "%s: Deleted\n", searchKey);
    }

    fprintf(out, "In Order: ");
    inorder(root, out);

    fclose(out);
    fclose(in);

    return 0;
}
