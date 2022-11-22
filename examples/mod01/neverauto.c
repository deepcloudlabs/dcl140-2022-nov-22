#include <stdio.h>

int another_function_call();

int main() {
   int *foo(int);
   int *yp;

   yp = foo(3);
   another_function_call(2);
   fprintf(stderr," %lx \n", yp );
   //fprintf(stderr," %d \n", *yp );
   return 0;
}

int *
foo( int p )
{
   int a;

   a = p + 2;
   return( &a );
}

int another_function_call(int t) {
  int i=42;
  return i%t;
}
