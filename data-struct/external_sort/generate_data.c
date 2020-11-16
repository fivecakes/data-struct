#include "generate_data.h"

#include <stdio.h>
#include <stdlib.h>


static char* genRandomString(char *string)
{
    for (int i = 0; i < 8; i++)
    {
        string[i] = 'a' + rand() % 26;
    }
    string[8] = ',';
    for (int i = 9; i < 25; i++)
    {
        string[i] = 'a' + rand() % 26;
    }
    string[25] = '\0';
    return string;
}


int generate_data()
{
    int MAX=80000000;
    
    FILE *fp = fopen("/tmp/test.txt", "w+");
    char *string = malloc(26 *sizeof(char));
    for(int i=0;i<MAX;i++){
        fprintf(fp, "%s\n", genRandomString(string));
    }
    fclose(fp);
    return 0;
}
