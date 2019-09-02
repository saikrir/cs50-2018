#include <stdio.h>
#include <cs50.h>
#include <string.h>


bool islowercase(int c) {
    if(c >= 'a' && c <= 'z') {
        return true;
    }
    return false;
}

bool isuppercase(int c) {
    if(c>='A' && c <= 'Z') {
        return true;
    }
    return false;
}

void printCipherText(string plainText, int cipherKey) {
    for (int i= 0; i < strlen(plainText); i++)
    {
        int ochar = plainText[i];
        int tchar = ochar;

        if(islowercase(ochar) || isuppercase(ochar)) {
            tchar = ochar + cipherKey;
            if ( (islowercase(ochar) && tchar >= 'z') ||  (isuppercase(ochar) && tchar >= 'Z')) {
                tchar = tchar - 26;
            }
        }
        printf("%c", tchar);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    if(argc!= 2) {
        printf("Invalid argument passed \n");
        return 1;
    }

    int cKey = atoi(argv[1]);
    if(cKey >= 26) {
        cKey = cKey % 26;
    }

    string userinput = get_string("plaintext: ");

    printCipherText(userinput, cKey);

    return 0;
}
