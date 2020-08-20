#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int cipher(string key);
int shift(char c);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Usage: ./vigenere keyword");
            return 1;
        }   
    }
    int key = shift(argv[1][0]);
    cipher(argv[1]);
    return 0;
}


int shift(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c - 65;
    }
    if (c >= 'a' && c <= 'z')
    {
        return c - 97;
    }
    return 1;
}

int cipher(string key)
{
    string plainText = get_string("plaintext: ");
    printf("ciphertext: ");
    char cipherText[strlen(plainText)];
    int j = 0;
    
    for(int i = 0; i < strlen(plainText); i++)
    {
        if (plainText[i] >= 'A' && plainText[i] <= 'Z')
        {
            if (j == strlen(key))
            {
                j = 0;
            }
            cipherText[i] = (plainText[i] + shift(key[j])) % 65 % 26 + 65;
            j += 1;
        }
        else if (plainText[i] >= 'a' && plainText[i] <= 'z')
        {
            if (j == strlen(key))
            {
                j = 0;
            }
            cipherText[i] = (plainText[i] + shift(key[j])) % 97 % 26 + 97;
            j += 1;
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
