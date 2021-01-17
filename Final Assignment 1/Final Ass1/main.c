/*COP 3502C Final term Assignment 1This program is written by: Justin Moy*/
#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
int radius;
int numberOfPoints;

typedef struct data{

    int x;
    int y;

}point;

int isWithin(point center, point other);

int compareTo(point one, point two);

void merge(point array[], int l, int m, int radius);

void mergeSort(point array[], int l, int r);

point* ReadData(FILE *input, point* center);

int numberWithinCircle(point ar[], int n, point center);

point* FilterData(int inside, int numberOfPoints, point *allPoints, point center);

void printArray(point *pointsInCircle, int inside);

int equals(point one, point two);

int BinarySearch(point* arr, int l, int r, point searchVal);

void SearchPhase(point *out, int size);

int main()
{
    FILE *input, *output;
    point center;
    point *allPoints;

    input = fopen("in.txt", "r");

    allPoints = ReadData(input, &center);

    int inside = numberWithinCircle(allPoints, numberOfPoints, center);
    point *pointsInCircle = FilterData(inside, numberOfPoints, allPoints, center);

    mergeSort(pointsInCircle, 0, inside-1);

    output = fopen("out.txt", "w");
    for(int i = 0; i < inside; i++){
        fprintf(output, "%d %d\n", pointsInCircle[i].x, pointsInCircle[i].y);
    }

    fclose(input);
    fclose(output);

    SearchPhase(pointsInCircle, inside);
    return 0;
}

int isWithin(point center, point other){

    int lx = other.x - center.x;
    int ly = other.y - center.y;
    int rad = (lx*lx) + (ly*ly);

    if(rad > (radius*radius)){
        return FALSE;
    }
    return TRUE;

}

void mergeSort(point array[], int l, int r){
    if(l < r){
        int m = (l + r)/2;

        mergeSort(array, l, m);
        mergeSort(array, m+1, r);

        merge(array, l, m, r);
    }
}

int compareTo(point one, point two){

    if(one.x - two.x < 0)
        return 1;
    if(two.x - one.x < 0)
        return 2;
    if(one.y - two.y < 0)
        return 1;
    else
        return 2;
}

void merge(point array[], int l, int m, int r){

    int s1 = m - l+1;
    int s2 = r - m;

    point L[s1];
    point R[s2];

    for(int i = 0; i < s1; i++){
        L[i] = array[l+i];
    }
    for(int i = 0; i < s2; i++){
        R[i] = array[m+1+i];
    }

    int t1 = 0;
    int t2 = 0;
    int t3 = l;

    while(t1 < s1 && t2 < s2){

        if(compareTo(L[t1], R[t2]) == 2){
            array[t3] = R[t2];
            t2++;
        }else{
            array[t3] = L[t1];
            t1++;
        }
        t3++;
    }

    while(t1 < s1){
        array[t3] = L[t1];
        t1++;
        t3++;
    }

    while(t2 < s2){
        array[t3] = R[t2];
        t2++;
        t3++;
    }
}

point* ReadData(FILE *input, point* center){

    fscanf(input, "%d", &center->x);
    fscanf(input, "%d", &center->y);
    fscanf(input, "%d", &radius);
    fscanf(input, "%d", &numberOfPoints);

    point *temp = (point*)malloc(numberOfPoints * sizeof(point));
    for(int i = 0; i < numberOfPoints; i++){

        fscanf(input, "%d", &temp[i].x);
        fscanf(input, "%d", &temp[i].y);
    }
    return temp;
}

int numberWithinCircle(point ar[], int n, point center){

    int c = 0;

    for(int i = 0; i < n; i++){
        if(isWithin(center, ar[i])== TRUE){
            c++;
        }
    }
    return c;

}

point* FilterData(int inside, int numberOfPoints, point *allPoints, point center){

    point *temp = (point*)malloc(inside * sizeof(point));
    int j = 0;
    for(int i = 0; i < numberOfPoints; i++){

        if(isWithin(center, allPoints[i]) == TRUE){
            temp[j] = allPoints[i];
            j++;
        }
    }

    return temp;
}

void printArray(point *pointsInCircle, int inside){
    for(int i = 0; i < inside; i++){
        printf("%d %d\n", pointsInCircle[i].x, pointsInCircle[i].y);
    }
    printf("\n\n");
}

int equals(point one, point two){

    if(one.x == two.x && one.y == two.y){
        return 1;
    }
    return 0;
}

int BinarySearch(point* arr, int l, int r, point searchVal){
    int m = (l+r)/2;
    if(l <= r){
        if(equals(arr[m], searchVal) == 1){
            return m+1;
        }
        if(compareTo(searchVal, arr[m]) == 1)
             return BinarySearch(arr, l, m-1, searchVal);
        else
            return BinarySearch(arr, m+1, r, searchVal);
    }else
        return 0;
}

void SearchPhase(point *out, int size){

    point searchVal;
    int x;

    do{

       printf("Enter points: ");
       scanf("%d", &searchVal.x);
       scanf("%d", &searchVal.y);

       if((x = BinarySearch(out, 0, size-1, searchVal)) > 0)
            printf("Found at record:  %d\n", x);
       else if (searchVal.x == -999 || searchVal.y == -999)
            printf("exit\n");
        else
            printf("Not Found\n");

    }while(searchVal.x != -999 && searchVal.y != -999);

}
