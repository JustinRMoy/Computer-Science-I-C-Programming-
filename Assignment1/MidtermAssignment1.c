/*COP 3502C Midterm Assignment OneThis program is written by: Justin Moy*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 50
#define EMPTY -1

typedef struct stack{

    char items [SIZE];
    int post[SIZE];
    char** str;
    int top; ///for char items[] and int post[]
    int topStr;
    int s;

}theStack;

theStack stackPtr;

int full(){

    return(stackPtr.top == SIZE - 1);

}

int empty(){

    if(stackPtr.top < 0) {
        return 1;
    } else {
        return 0;
    }

}

int top(){

    if(empty(stackPtr)){
        return EMPTY;
    }

    return stackPtr.items[stackPtr.top];

}

void push(char val){ //!/////////////////////////////PUSH

    if(full()){
        printf("Stack is Full");
    }else{
        stackPtr.items[stackPtr.top+1] = val;
        (stackPtr.top)++;
    }
    return;
}

void pushStr(char val){//!//////////////////////////////push STR

    if(full()){
        printf("Stack is Full");
    }else{
        stackPtr.items[stackPtr.topStr+1] = val;
        (stackPtr.topStr)++;
    }
    return;
}

void pushInt(int val){

    if(stackPtr.top >= SIZE-1){
        printf("Stack is Full");
    }else{
        stackPtr.post[stackPtr.top+1] = val;
        (stackPtr.top)++;
    }
}

int popInt(){

    int val;
    if(stackPtr.top == -1){
        printf("Stack is empty");
        return '0';
    }

    val = stackPtr.post[stackPtr.top];
    (stackPtr.top)--;

    return val;

}

char pop(){//!?////////////////////////////////POP

    char val;
    if(stackPtr.top == -1){
        printf("Stack is empty");
        return '0';
    }

    val = stackPtr.items[stackPtr.top];
    (stackPtr.top)--;

    return val;

}

char popStr(){//!//////////////////////////////POP STR

    char val;
    if(stackPtr.topStr == -1){
        printf("Stack is empty");
        return '0';
    }

    val = stackPtr.items[stackPtr.topStr];
    (stackPtr.topStr)--;

    return val;

}

char* menu(){

    char *userInput = (char*)malloc(50 * sizeof(char));
    char c;
    int k = 0;

    printf("Press e to enter your infix\nPress x to exit the program\n");
    scanf("%s", userInput);

    if(strcmp(userInput, "e") == 0){
        printf("Enter infix: ");
        while((c = getchar()) != '\n' && c != EOF);
        scanf("%[^\n]s", userInput);
        for(int i = 0; i < strlen(userInput); i++){
            if(userInput[i] == ' '){
                    k++;
                for(int j = i; j < strlen(userInput)-1; j++){
                    userInput[j] = userInput[j+1];
                }
            }
        }
        userInput[strlen(userInput)-k] = '\0';
        return userInput;
    }
    sprintf(userInput, "exit");
    return userInput;


}

int isBalancedParenthesis(char* in){

    char let = '0';
    stackPtr.top = EMPTY;
    for(int i = 0; i < strlen(in); i++){
        if(in[i] == '(' || in[i] == '[' || in[i] == '{'){
            push(in[i]);

        }else if(in[i] == ')' || in[i] == ']' || in[i] == '}'){

            if(empty() == 1){
                stackPtr.top = EMPTY;
                return 0;
            }

            let  = pop();

            if(let != '(' && in[i] == ')' || let != '[' && in[i] == ']' || let != '{' && in[i] == '}'){
                stackPtr.top = EMPTY;
                return 0;
            }
        }
    }

    if(empty() == 0){
        stackPtr.top = EMPTY;
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

int convertStrToInt(char* post){

    int retval = 0;
    int j = strlen(post);
    for(int i = 0; i < strlen(post); i++){
        retval += convetToInt(post[i]) * power(10, j-1);
        j--;
    }
    return retval;

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


char** convertToPostfix(char* infix){

    char **postStr = (char**)malloc(SIZE * sizeof(char*));
    for(int i = 0; i < SIZE; i++){
        postStr[i] = (char*)malloc(SIZE * sizeof(char));
    }

    int j = 0;
    int val;
    int k;
    stackPtr.s = 0;

    for(int i = 0; i < strlen(infix); i++){
        k = 0;

        if(isOperator(infix[i]) == 1){

            if(getOperatorPriority(infix[i]) == 0){
                pushStr(infix[i]);
            }else if(getOperatorPriority(infix[i]) == 4){
                while(getOperatorPriority(stackPtr.items[stackPtr.topStr]) != 0){ //post[j] = pop(stackPtr);
                    postStr[j][0] = popStr();
                    j++;
                    stackPtr.s++;
                }
                (stackPtr.topStr)--;
            }else if(getOperatorPriority(infix[i]) <= getOperatorPriority(stackPtr.items[stackPtr.topStr]) ){

                while(getOperatorPriority(infix[i]) <= getOperatorPriority(stackPtr.items[stackPtr.topStr]) ){
                    postStr[j][0] = popStr();
                    j++;
                    stackPtr.s++;
                }

                pushStr(infix[i]);
            }else{
                pushStr(infix[i]);
            }

        }else{

            while(isOperator(infix[i]) == 0 && i < strlen(infix)){
                postStr[j][k] = infix[i];
                k++;
                i++;
            }
            j++;
            stackPtr.s++;
            i--;
        }
    }

    while(stackPtr.topStr > -1){
        postStr[j][0] = popStr();
        j++;
        stackPtr.s++;
    }

    printf("Postfix is: ");
    for(int i = 0; i < stackPtr.s; i++){
        printf("%s ", postStr[i]);
    }
        printf("\n");
    return postStr;
}

void evaluate(char** post){

 int ans = 0;
 int a, b;
    for(int i = 0; i < stackPtr.s; i++){

        if(isOperator(post[i][0])){
            b = popInt(stackPtr);
            a = popInt(stackPtr);
            ans = calculate(a,b,post[i][0]);
            pushInt(ans);
        }else{

            pushInt(convertStrToInt(post[i]));
        }
    }
    printf("Evaluation: %d\n", ans);

}

void init(){

    stackPtr.top = -1;
    stackPtr.topStr = -1;
    stackPtr.str = (char**)malloc(SIZE * sizeof(char*)); ///string array
    stackPtr.s = 0;

    for(int i = 0; i < SIZE; i++){
        stackPtr.str[i] = (char*)malloc(SIZE * sizeof(char));///initialize string array
    }

}

int main()
{
    init();
    char *str;
    char **postFix;
    char c;

    while(strcmp(str = menu(), "exit") != 0){

        if (isBalancedParenthesis(str)){
            postFix = convertToPostfix(str);
            evaluate(postFix);
        }else{
            printf("\nImbalance parenthesis\n");
        }
        free(str);
        while((c = getchar()) != '\n' && c != EOF);
    }

    free(str);
    for(int i = 0; i < stackPtr.s; i++){
        free(postFix[i]);  ///postFix STR
    }
    free(postFix);

    return 0;
}

