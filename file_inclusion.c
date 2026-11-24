#include "preprocessor.h"
void handle_include(FILE *src, FILE *dest)
{
    char line[1024];
    char filename[100];
    FILE *fp;
    int ch;

    while (fgets(line, sizeof(line), src))
    {
        // User-defined header
        if (sscanf(line, "#include \"%99[^\"]\"", filename) == 1)
        {
            fp = fopen(filename, "r");

            if (fp == NULL)
            {
                printf("Error: Cannot open include file %s\n",
                       filename);
                continue;
            }

            while ((ch = fgetc(fp)) != EOF)
                fputc(ch, dest);

            fclose(fp);
        }
        // System header
        else
        {
            fputs(line, dest);
        }
    }
}

