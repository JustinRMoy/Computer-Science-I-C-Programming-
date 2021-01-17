/*COP 3502C Midterm Assignment OneThis program is written by: Justin Moy*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 50

typedef struct stack{

    char items [SIZE];
    int post[SIZE];
    int top;

}theStack;

void push(theStack* stackPtr, char val){

    if(stackPtr->top >= SIZE-1){
        printf("Stack is Full");
    }else{
        stackPtr->items[stackPtr->top+1] = val;
        (stackPtr->top)++;
    }
}

void pushInt(theStack* stackPtr, int val){

    if(stackPtr->top >= SIZE-1){
        printf("Stack is Full");
    }else{
        stackPtr->post[stackPtr->top+1] = val;
        (stackPtr->top)++;
    }
}

int popInt(theStack* stackPtr){

    int val;
    if(stackPtr->top == -1){
        printf("Stack is empty");
        return '0';
    }

    val = stackPtr->post[stackPtr->top];
    (stackPtr->top)--;

    return val;

}

char pop(theStack* stackPtr){

    char val;
    if(stackPtr->top == -1){
        printf("Stack is empty");
        return '0';
    }

    val = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;

    return val;

}

char* menu(){

    char *userInput = (char*)malloc(50 * sizeof(char));
    char c;

    printf("Press e to enter your infix\nPress x to exit the program\n");
    scanf("%s", userInput);

    if(strcmp(userInput, "e") == 0){
        printf("Enter infix: ");
        while((c = getchar()) != '\n' && c != EOF);
        scanf("%[^\n]s", userInput);
        return userInput;
    }
    sprintf(userInput, "exit");
    return userInput;


}

int isBalancedParenthesis(theStack* stackPtr, char* in){

    char let = '0';
    for(int i = 0; i < strlen(in); i++){
        if(in[i] == '('){
            push(stackPtr, in[i]);

        }else if(in[i] == ')'){
            let  = pop(stackPtr);

            if(let != '(' && in[i] == ')'){
                stackPtr->top = -1;
                return 0;
            }
        }
    }
    if(stackPtr->top != -1){
        stackPtr->top = -1;
        return 0;
    }
    return 1;

}

int isOperator(char c){

    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' || c == '(' || c == ')'){
        return 1;
    }else{
        return 0;
    }

}

int getOperatorPriority(char c){

    if(c == ')'){
        return 4;
    }else if(c == '^'){
        return 3;
    }else if(c == '*' || c == '/' || c == '%'){
        return 2;
    }else if(c == '+' || c == '-'){
        return 1;
    }else{
        return 0;
    }

}

int convetToInt(char c){

    return c - '0';

}

int power(int a, int b){

    int j = 1;
    for(int i = 0; i < b; i++){
        j *= a;
    }
    return j;

}

int calculate(int a, int b, char op){

    if( op == '+'){
        return a + b;
    }else if( op == '-'){
        return a - b;
    }else if( op == '*'){
        return a * b;
    }else if( op == '/'){
        return a / b;
    }else if( op == '%'){
        return a % b;
    }else{
        return power(a, b);
    }

}

int twoDig(int a, int b){

    int v = a * 10;
    v += b;
    return v;

}
/*
char* convertToPostfix(theStack* stackPtr, char* infix){

    char *post = (char*)malloc(SIZE * sizeof(char));
    int j = 0;

    for(int i = 0; i < strlen(infix); i++){

        if(isOperator(infix[i]) == 1){

            if(getOperatorPriority(infix[i]) == 0){
                push(stackPtr, infix[i]);
            }else if(getOperatorPriority(infix[i]) == 4){
                while(getOperatorPriority(stackPtr->items[stackPtr->top]) != 0){
                    post[j] = pop(stackPtr);
                    j++;
                }
                (stackPtr->top)--;
            }else if(getOperatorPriority(infix[i]) <= getOperatorPriority(stackPtr->items[stackPtr->top]) ){

                while(getOperatorPriority(infix[i]) <= getOperatorPriority(stackPtr->items[stackPtr->top]) ){
                    post[j] = pop(stackPtr);
                    j++;
                }

                push(stackPtr, infix[i]);
            }else{
                push(stackPtr, infix[i]);
            }

        }else{
            post[j] = infix[i];
            j++;
        }
    }

    while(stackPtr->top > -1){
        post[j] = pop(stackPtr);
        j++;
    }

    return post;
}
*/
char* convertToPostfix(theStack* stackPtr, char* infix){

    char *post = (char*)malloc(SIZE * sizeof(char*));
    for(int i = 0; i < strlen(post); i++){
        post[i] = (char*)malloc(SIZE * sizeof(char));
    }
    int j = 0;

    for(int i = 0; i < strlen(infix); i++){

        if(isOperator(infix[i]) == 1){

            if(getOperatorPriority(infix[i]) == 0){
                push(stackPtr, infix[i]);
            }else if(getOperatorPriority(infix[i]) == 4){
                while(getOperatorPriority(stackPtr->items[stackPtr->top]) != 0){
                    post[j] = pop(stackPtr);
                    j++;
                }
                (stackPtr->top)--;
            }else if(getOperatorPriority(infix[i]) <= getOperatorPriority(stackPtr->items[stackPtr->top]) ){

                while(getOperatorPriority(infix[i]) <= getOperatorPriority(stackPtr->items[stackPtr->top]) ){
                    post[j] = pop(stackPtr);
                    j++;
                }

                push(stackPtr, infix[i]);
            }else{
                push(stackPtr, infix[i]);
            }

        }else{
            post[j] = infix[i];
            j++;
        }
    }

    while(stackPtr->top > -1){
        post[j] = pop(stackPtr);
        j++;
    }

    return post;
}

void evaluate(char* post){

 int ans = 0;
 int a, b;
    for(int i = 0; i < strlen(post); i++){
        if(isOperator(post[i]) == 1){
            a = convetToInt(post[i-2]);
            b = convetToInt(post[i-1]);
            ans += calculate(a,b,post[i]);
        }
    }

}
int main()
{
    char n = 97;
    printf("%c", n);
   /* theStack arr;

    arr.top = -1;
    arr.post = (char*)malloc(SIZE * sizeof(char*));

    for(int i = 0; i < strlen(arr.post); i++){
        arr.post[i] = (char*)malloc(SIZE * sizeof(char));
    }

    char *str = (char*)malloc(SIZE * sizeof(char));
    char *postFix = (char*)malloc(SIZE * sizeof(char));

    str = menu();
    while(strcmp(str, "exit") != 0){
        if (isBalancedParenthesis(&arr, str) == 1){
            postFix = convertToPostfix(&arr, str);
            printf("%s\n", postFix);
            //evaluate(postFix);
            str = menu();
        }else if(isBalancedParenthesis(&arr, str) == 0){
            printf("Parenthesis imbalanced\n");
            str = menu();
        }
    }

    free(str);
    free(postFix);*/
    return 0;
}
