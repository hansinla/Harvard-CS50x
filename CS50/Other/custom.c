#include <cs50.h>
#include <stdio.h>

int main(void){
    string name;
    printf("What is your name?\n");
    name = GetString();
    printf("Hello %s.\n", name);

    return 0;
}
