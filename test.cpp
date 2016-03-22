#include <stdio.h>
#include "Vector.h"
#include <stdlib.h>
#include "Matrix.h"

int main() {
    //printf("Hello World!\n");
    Vector* v1 = new Vector(3,0.225,0,0);
    Vector* v2 = new Vector(3,0.9390,0.3438,0);
    Vector* v3 = new Vector(3,4,9,17);
    Vector* v4 = &(*v1 ^ *v2);
    Matrix* mt = new Matrix(v1,v2,v3);
    Vector result = mt->solution(*v4);
    char* s = mt->printM();
    char* x = v4->printV();
    char* z = result.printV();
    printf("%s\n%s\n%s\n%d\n",s,x,z,mt(1,2));
    exit(EXIT_SUCCESS);
}
