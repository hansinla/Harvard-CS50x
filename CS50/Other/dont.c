#include <stdio.h>

void foo(int x)
{
    //printf("Don't do this\t%d\n", x);
    x++;
    foo(x);
}

int main(void)
{
    int x = 1;
    foo(0);
    return 0;
}
