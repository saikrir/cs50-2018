#include <stdio.h>
#include <cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char *salt = "50";
    if(argc !=2) {
        printf("Invalid usage");
        return 1;
    }

    const char *hash = argv[1];

    for(int i = 0; i < 5; i++ ) {
        char word[] =  { '\0', '\0', '\0', '\0','\0' };
        
    }
    
    return 0;
}
