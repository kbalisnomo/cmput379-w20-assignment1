#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    // waste time
    int i,j; 
    for (i=0,j=0; i<2147483647; i++) { 
        j+=i*i;
        j-=i*i;
        j+=i*i;
    }     
    printf("Hello World\n");
    return 0;
}
