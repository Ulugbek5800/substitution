#include <stdio.h>
#include <string.h>
#include <ctype.h>

// USEFUL NOTES
// *argv = argv[]   // *argv[] = **argv = argv[][]  // it points to the pointer
// ["string 1", "string 2", "string 3", ...]    // "string 1" = ['s', 't', 'r', 'i', 'n', 'g', ' ', '1']
// argv[1] = "string 2", *argv[1] = 's'     // argv[1] = *(argv + 1), *argv[1] = *(*(argv + 1))

char *letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";   // used for converting plaintext (*letters) to ciphertext (key, or argv[1])

int main(int argc, char *argv[])    // int argc - number of command line arguments  // char *argv[] - array of strings, ["./a.exe", "key"]
{
    char plain[128], cipher[128];

    // checking if command has 2 arguments
    if (argc < 2)
    {
        printf("You have entered less than 2 arguments\n");
        printf("Usage: ./file KEY");
        return 1;
    }
    else if (argc > 2)
    {
        printf("You have entered more than 2 arguments\n");
        printf("Usage: ./file KEY");
        return 1;
    }

    // checking if the key is valid
    if (strlen(argv[1]) != 26)      // argv[1] is the key (string)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        argv[1][i] = toupper(argv[1][i]);   // making all letters uppercase
    }
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (argv[1][i] == argv[1][j])   // all letters should be uppercase
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    // getting plaintext from the user
    printf("plaintext: ");
    scanf("%[^\n]c", plain);

    // plaintext -> ciphertext      // check "This is CS50.", "ABCDEFGHIJKLMNOPQRSTUVWXYZ" -> "QWERTYUIOPASDFGHJKLZXCVBNM"
    for (int i = 0, len = strlen(plain); i < len; i++)
    {
        if (isalpha(plain[i]))
        {
            for (int j = 0; j < 26; j++)
            {
                if (toupper(plain[i]) == letters[j])    // *letters - alphabetized string
                {
                    if (isupper(plain[i]))
                        cipher[i] = argv[1][j];         // *argv[1] - key for ciphering
                    else if (islower(plain[i]))
                        cipher[i] = tolower(argv[1][j]);
                    break;
                }
            }
        }
        else
        {
            cipher[i] = plain[i];
        }
    }

    // printing ciphertext
    printf("ciphertext: %s\n", cipher);

    return 0;
}
