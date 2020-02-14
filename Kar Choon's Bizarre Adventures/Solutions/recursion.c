#include<stdio.h>
int factorial_for(int);
int factorial_res(int);
void fibo_for(int);

int main(void) {
    int factorial = 10;
    int fibo_step = 10;
    printf("Using the for loop method: %i! =  %i\n",factorial, factorial_for(factorial));
    printf("Using the recursive method: %i! =  %i\n",factorial, factorial_res(factorial));
    printf("Fibonacci Sequence in %i steps: \n", fibo_step);
    fibo_for(fibo_step);
    printf("Fibonacci Sequence in %i steps: \n", fibo_step);
    for (int i=0; i<=fibo_step; i++) {
      printf("%i\n", fibo_res(i));
    }
    return(0);
}

int factorial_for (int num) {
    int res = 1;
    for (int i = 1; i <= num; i++) {
        res = res*i;
    }
    return res;
}

int factorial_res (int num) {
  if (num>1) { return num*factorial_res(num-1);}
  return 1;
}

void fibo_for (int num) {
  int prev2 = 0; int prev = 1; int sum = 0;
  for (int i=0; i<=num; i++) {
    if (i<2) { printf("%i\n", i); }
    else {
      sum = prev + prev2;
      printf("%i\n",sum);
      prev2 = prev;
      prev = sum;
    }
  }
}

int fibo_res (int num) {
  if (num == 0) { return 0; }
  if (num == 1) { return 1; }
  return fibo_res(num-1) + fibo_res(num-2);
}
