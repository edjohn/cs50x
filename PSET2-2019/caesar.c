#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int cipher(int shift);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
            printf("Usage: ./caesar key");
            return 1;
        }   
    }
    int shift = atoi(argv[1]);
    
    cipher(shift);
}


int cipher(int shift)
{
    string plainText = get_string("plaintext: ");
    printf("ciphertext: ");
    char cipherText[strlen(plainText)];

    for(int i = 0; i < strlen(plainText); i += 1)
    {
        if (plainText[i] >= 'A' && plainText[i] <= 'Z')
        {
            cipherText[i] = (plainText[i] + shift) % 65 % 26 + 65;
        }
        else if (plainText[i] >= 'a' && plainText[i] <= 'z')
        {
            cipherText[i] = (plainText[i] + shift) % 97 % 26 + 97;
        }
        else
        {
            cipherText[i] = plainText[i];
        }
        printf("%c", cipherText[i]);
    }
    printf("\n");
    return 0;
}


