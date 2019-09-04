#include <stdio.h>
#include <cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *salt = "50";
    if(argc != 2) {
        printf("Invalid usage");
        return 1;
    }

    const char *hash = argv[1];    
    for (int i = 'A'; i <= 'z'; i++) {
        
        char word[] =  { '\0', '\0', '\0', '\0','\0' };
        
        if(i > 'Z' && i < 'a') {
            continue;
        }
        
        for (int j = 'A'; j <= 'z'; j++) {
            if(j > 90 && j < 97) {
                continue;
            }
            
            for (int k = 'A'; k <= 'z'; k++) {
                if(k > 'Z' && k < 'a') {
                    continue;
                }                
                for (int l = 'A'; l <= 'z'; l++) {
                    if(l > 'Z' && l < 'a') {
                        continue;
                    }
                    //printf("%c%c%c%c \n", i, j, k, l);
                    
                    word[0] = i;
                    word[1] = j;
                    word[2] = k;
                    word[3] = l;
                    
                    if(strcmp(hash, crypt(word, salt)) == 0) {
                        printf("CRACKED !!  %s", word);
                        return 0;
                    }
                }
                //printf("%c%c%c \n", i, j, k);
                word[0] = i;
                word[1] = j;
                word[2] = k;
                if(strcmp(hash, crypt(word, salt)) == 0) {
                    printf("CRACKED !!  %s", word);
                    return 0;
                }
            }
            
            //printf("%c%c \n", i, j);
            word[0] = i;
            word[1] = j;
            
            if(strcmp(hash, crypt(word, salt)) ==0) {
                printf("CRACKED !!  %s", word);
                return 0;
            }
        }
        word[0] = i;
        
        if(strcmp(hash, crypt(word, salt)) == 0 ) {
            printf("CRACKED !!  %s", word);
            return 0;
        }
        //printf("%c \n", i);
    }
    
    printf("\n");
    return 0;
}
