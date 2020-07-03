  
/**
 * @file Utils.c
 * 
 * @brief Provides an implementation of the all the operations defined in the Utils module
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Utils.h"
#include "Region.h"
#include "Patient.h"
#include "Date.h"

int loadRegionIntoMap(char *path, PtMap ptMap)
{
    // Check if map is null
    if (ptMap == NULL)
    {
        printf("An error ocurred... Map is null!\n");
        return MAP_NULL;
    }

    // Check if file in path is not null
    FILE *file = NULL;
    file = fopen(path, "r");
    if(file == NULL)
    {
        printf("Could not open file %s\n", path);
        return UTIL_FILE_NULL;
    }

    char nextLine[128];         // holds each line of file
    int line_count;             // hold how many lines are in the file
    countEntries(path, &line_count);

    // Fill map with values
    bool isFirstLine = true;
    while(line_count-- > 0 && fgets(nextLine, sizeof(nextLine), file))
    {
        // Skip headers
        if(isFirstLine)
        {
            isFirstLine = false;
            continue;
        }

        // Remove commas from lines
        removeChar(nextLine, ',');
        char **tokens = split(nextLine, 6, ";");
        
        // Create region to add to the map. strlen() + 1 to make up for '\0' character
        char *key = (char *)malloc((strlen(tokens[0]) + 1) * sizeof(char));
        strcpy(key, tokens[0]);

        // Region to put in map as value
        PtRegion region = regionCreate(tokens[0], tokens[1], atoi(tokens[2]), atoi(tokens[3]));

        int error_code = mapPut(ptMap, key, region);
        free(tokens);

        if(error_code == MAP_FULL)
        {
            printf("An error ocurred... Map is full!");
            return MAP_FULL;
        }
    }
    
    fclose(file);

    return UTIL_OK;
}

int loadPatientsIntoList(char *path, PtList ptList)
{
    // Check if list is null
    if(ptList == NULL)
    {
        printf("An error ocurred... List is null!\n");
        return LIST_NULL;
    }

    // Check if file in path is not null
    FILE *file = NULL;
    file = fopen(path, "r");
    if(file == NULL)
    {
        printf("Could not open file %s\n", path);
        return UTIL_FILE_NULL;
    }

    char nextLine[1024];    // holds each line of file
    int line_count;         // hold how many lines are in the file
    countEntries(path, &line_count);

    bool isFirstLine = true;
    int rank = 0;
    
    // Fill List with values
    while(rank < line_count && fgets(nextLine, sizeof(nextLine), file))
    {
        // Skip headers
        if(isFirstLine)
        {
            isFirstLine = false;
            continue;
        }

        // Remove commas from lines
        removeChar(nextLine, ',');
        char **tokens = split(nextLine, 11, ";");

        // Convert string to long ints
        long int patient_id = strtol(tokens[0], NULL, 10);
        long int infected_by = strtol(tokens[6], NULL, 10);

        // Handle Dates
        PtDate confirmed_date, release_date, decease_date;
        parseDate(tokens[7], &confirmed_date);
        parseDate(tokens[8], &release_date);
        parseDate(tokens[9], &decease_date);

        // Infected reason
        tokens[5] = (strlen(tokens[5]) == 0) ? "unknown" : tokens[5];

        /** Last character two of this string are a line break. This removes them */
        tokens[10][strlen(tokens[10])-2] = '\0';
        
        PtPatient patient = patientCreate(
            patient_id,                                         // id
            (strlen(tokens[1]) == 0) ? "" : tokens[1],          // sex
            (strlen(tokens[2]) == 0) ? -1 : atoi(tokens[2]),    // birthYear
            (strlen(tokens[3]) == 0) ? "" : tokens[3],          // country
            tokens[4],                                          // PtRegion
            tokens[5],                                          // infectionReason
            (infected_by == 0) ? -1 : infected_by,              // infectedBy
            confirmed_date,                                     // confirmed date
            release_date,                                       // released date
            decease_date,                                       // decease date
            tokens[10]                                          // status
        );
        
        free(tokens);
        listAdd(ptList, rank++, patient);
    }
    fclose(file);
    
    return UTIL_OK;
}

char** split(char *string, int nFields, const char *delim) 
{
    char **tokens = (char**) malloc(sizeof(char*) * nFields);

    int index = 0;
    int len = strlen(string);
    
    tokens[index++] = &string[0];
    for(int i = 0; i < len; i++) 
    {
        if( string[i] == delim[0] ) 
        {
            string[i] = '\0';
            if(i < len - 1) 
            {
                tokens[index++] = &string[i] + 1;
            }           
        }
    }
    
    return tokens;
}

int countEntries(char *path, int *total)
{
    FILE *file = NULL;
    char fileChar;

    file = fopen(path, "r");
    if(file == NULL) return UTIL_FILE_NULL;

    *total = 0;
    for (fileChar = getc(file); fileChar != EOF; fileChar = getc(file)) 
    {
        if(fileChar == '\n')
        {
            *total = *total + 1;
        }
    }

    fclose(file);

    return UTIL_OK;
}

void removeChar(char *str, char remove)
{
    int size = strlen(str);

    int j = 0;
    for(int i = 0; i < size ; i++)
    {
        if(str[i] != remove)
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int destroyStringRegionMap(PtMap *ptMap)
{
    if(ptMap == NULL) return MAP_NULL;

    PtMap map = *ptMap;
    int size;
    mapSize(map, &size);

    // Free Values
    MapValue *values = mapValues(map);
    MapKey *keys = mapKeys(map);
    for(int i = 0; i < size; i++)
    {
        regionDestroy(&values[i]);
        free(keys[i]);
    }

    free(keys);
    free(values);
    mapDestroy(ptMap);
    ptMap = NULL;

    return MAP_OK;
}

int destroyPatientList(PtList *ptList)
{
    PtList list = *ptList;

    int size;
    listSize(list, &size);

    for(int i = size - 1; i >= 0; i--)
    {
        PtPatient patient;
        int error = listRemove(list, i, &patient);
        if(error != 0) printf("LIST_REMOVE ERROR: %d\n", error);
        
        patientDestroy(&patient);
    }

    listDestroy(&list);
    
    return LIST_OK;
}

void parseDate(char *date_str, PtDate *date)
{
    /**
     * In patients.csv there's a patient with ID 2000000039 that has a malformed deceased date
     * Not only it's separated by '-' instead of '/', but it's format is YYYY/MM/DD
     * We are ignoring this date and creating a default value for it
     */
    if(strlen(date_str) == 0)
    {
        *date = dateCreate(0, 0, 0);
        return;
    }

    char **tokens = split(date_str, 3, "/");
    *date = dateCreate(atoi(tokens[0]) ,atoi(tokens[1]), atoi(tokens[2]));
    free(tokens);
}

int equalsStringIgnoreCase(char str1[], char str2[]) 
{
	int len = strlen(str1);
	for(int i = 0; i < len; i++) 
	{
		if(str1[i] > 96 && str1[i] < 123) 
		{
			str1[i] = str1[i] - 32;
		}
	}
	return (strcmp(str1, str2) == 0);
}

void clearMemory(PtList *list, PtMap *map)
{
    if(*list != NULL) 
	{
		printf("\n<< Patients list cleared! >>\n");
		destroyPatientList(list);
        *list = NULL;
	}
	if(*map != NULL) 
	{
		printf("\n<< Regions map cleared! >>\n\n");
		destroyStringRegionMap(map);
        *map = NULL;
    }
}