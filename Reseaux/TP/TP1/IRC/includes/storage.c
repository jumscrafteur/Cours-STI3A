#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utils.h"
#include "storage.h"

#define DB_FILE_NAME "db_file.txt"
#define DB_TEMP_FILE_NAME "db_tempfile.txt"

void appendKeyValuePair(char *key, char *value)
{
    FILE *fp;

    fp = fopen(DB_FILE_NAME, "a");

    fprintf(fp, "%s:%s\n", key, value);

    fclose(fp);
}

int getValueFromKey(char *key, char *out)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *value;
    int find = -1;

    fp = fopen(DB_FILE_NAME, "r");

    while ((read = getline(&line, &len, fp)) != -1)
    {
        value = strchr(line, ':');
        if (value != NULL)
        {
            *value = '\0';
            value++;
            if (strcmp(line, key) == 0)
            {
                find = 0;
                value[strcspn(value, "\n")] = '\0';
                strcpy(out, value);
                break;
            }
        }
    }

    fclose(fp);

    if (line)
    {
        free(line);
    }

    return find;
}

void removeKeyValuePair(char *key)
{
    FILE *fp, *fp_temp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *value;

    if ((fp = fopen(DB_FILE_NAME, "r")) == NULL || (fp_temp = fopen(DB_TEMP_FILE_NAME, "w")) == NULL)
        stop("Erreur : fopen\n");

    while ((read = getline(&line, &len, fp)) != -1)
    {
        // Extract the key and value from the current line
        value = strchr(line, ':');
        if (value != NULL)
        {
            *value = '\0';
            value++;
            if (strcmp(line, key) != 0)
                fprintf(fp_temp, "%s:%s", line, value);
        }
    }

    if (line)
    {
        free(line);
    }
    // Close both files
    fclose(fp);
    fclose(fp_temp);

    // Delete the original file
    if (remove(DB_FILE_NAME) != 0)
    {
        printf("Error deleting original file.\n");
    }

    // Rename the temporary file
    if (rename(DB_TEMP_FILE_NAME, DB_FILE_NAME) != 0)
        stop("Erreur : rename");
}

void updateValueFromKey(char *key, char *value)
{
    removeKeyValuePair(key);
    appendKeyValuePair(key, value);
}

bool isKeyInStorage(char *key)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *value;

    fp = fopen(DB_FILE_NAME, "r");

    while ((read = getline(&line, &len, fp)) != -1)
    {
        value = strchr(line, ':');
        if (value != NULL)
        {
            *value = '\0';
            value++;
            if (strcmp(line, key) == 0)
            {
                return true;
            }
        }
    }

    return false;
}