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


bool isValidChar(int asciichar) {
 
    bool isvalid = false;
    
    if((asciichar >= 'A' && asciichar <= 'Z') || 
            (asciichar >= 'a' && asciichar <= 'z') ) {
        isvalid = true;
    } 

    return isvalid;
} 

bool isValidKey(const char *keyword) {
    bool isvalid  = true;
    for (int i = 0; i < strlen(keyword); i++)
    {
        if(!isValidChar(keyword[i])) {
            isvalid = false;
            break;
        }
    }
    return isvalid;
}

int getKeyCode(char keyChar) {

    int keyCode = -1;
    if(islowercase(keyChar)) {
        keyCode = keyChar - 'a';
    }
    else if(isuppercase(keyChar)) {
        keyCode = keyChar - 'A';
    }

    return keyCode;
}

void printVegenreCipher(char *plainText, const char *keyword) {
    
    int keyLength = strlen(keyword);

    for (int i  = 0, keyIndex = 0; i < strlen(plainText); i++)
    {
        int plainChar = plainText[i];

        if(keyIndex >= keyLength) {
            keyIndex = (keyIndex % keyLength);
        }

        if(isValidChar(plainChar)) {
            int cipherChar = plainChar + getKeyCode(keyword[keyIndex++]);
            if ( (islowercase(plainChar) && cipherChar > 'z') || (isuppercase(plainChar) && cipherChar > 'Z')) {
                cipherChar = cipherChar - 26;
            }
            printf("%c", cipherChar);
        }else {
             printf("%c", plainChar);
        }
    }
    
    printf("\n");
}

int main(int argc, char const *argv[])
{
    string key = NULL;
    if(argc != 2) {
        printf("error: Usage: ./vigenere k \n");
        return 1;
    }

    const char *keyword = argv[1];
    if(!isValidKey(keyword)) {
        printf("error KEY : ./vigenere k \n");
        return 1;
    }
    string plainText = get_string("plaintext: ");
    printVegenreCipher(plainText, keyword);
    return 0;
}
