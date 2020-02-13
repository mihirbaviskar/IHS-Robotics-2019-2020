#include<stdio.h>
int factorial(int);
int main() {
    printf("%i",factorial(4));
    return 0;
}

int factorial (int num) {
    int res = 1;
    for (int i = 1; i <= num; i++) {
        res = res*i;
    }
    return res;
}
