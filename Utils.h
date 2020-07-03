/**
 * @file Utils.h
 * 
 * @brief Defines helper operations to solve a wide range of problems 
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#pragma once

#include "lib/ADTMap/map.h"
#include "lib/ADTList/list.h"

#define UTIL_OK 0
#define UTIL_FILE_NULL 6

/**
 * @brief Loads data from given csv file with region, 'path', into a Map<char*, Region> 
 * 
 * @param path [in] to the csv file with the values to be loaded
 * @param map [out] ADDRESS of map to be filled with values of regions
 * 
 * @return int UTIL_OK if success or,
 * @return int MAP_NULL if map given by ADDRESS is null or,
 * @return int MAP_FULL if map has no space to fit all regions or,
 * @return int UTIL_FILE_NULL if file in 'path' could not be loaded
 */
int loadRegionIntoMap(char *path, PtMap ptMap);

/**
 * @brief Loads data from a given csv file with patients, 'path', into a List of type Patient
 * 
 * @param path [in] to the csv file with the values to be loaded
 * @param ptMap [in] map with all regions 
 * @param ptList [out] ADDRESS of list to be filled with patients
 * 
 * @return int UTIL_OK if success or,
 * @return int LIST_NULL if list given by ADDRESS is null or,
 * @return int LIST_FULL if list given has no space to fit all patients
 * @return int UTIL_FILE_NULL if file in 'path' could not be loaded
 */
int loadPatientsIntoList(char *path, PtList ptList);

/**
 * @brief Splits a 'string' every 'delim' into a 'nFields' long array of arrays
 * 
 * @param string [in] string to split
 * @param nFields [in] split array size
 * @param delim [in] where to split the string
 * 
 * @return char** pointer to created array
 */
char** split(char *string, int nFields, const char *delim);

/**
 * @brief Counts how many entries (lines) a given file in 'path' has.
 * 
 * @param path [in] to the file 
 * @param total [out] address of variable to hold total entries
 * 
 * @return UTIL_OK if success, or
 * @return UTIL_FILE_NULL if no file was loaded
 */
int countEntries(char *path, int *total);

/**
 * @brief Removes a character 'remove' from a string 'str'
 * 
 * @param str [in] string to have a character removed from
 * @param remove [in] character to be removed from 'str'
 */
void removeChar(char *str, char remove);

/**
 * @brief Frees all resources allocated to a map with key,value as char*,region 
 * 
 * @param ptMap [in] Map to destroy
 * 
 * @return int MAP_OK if success or,
 * @return int MAP_NULL if map is null
 */
int destroyStringRegionMap(PtMap *ptMap);

/**
 * @brief Frees all resources allocated to a patient list
 * 
 * This functions takes the list of patients AND the map containing all the Regions where
 * the patient->region pointers are taken from. This functions handles the destruction of 
 * both at the same time to make sure everything is destroyed in it's correct order
 * 
 * @param ptList [in] list to destroy
 * @param ptMap [in] map to destroy
 * 
 * @return int LIST_OK is success or,
 * @return int LIST_NULL if list is null
 */
int destroyPatientList(PtList *ptList);

/**
 * @brief Converts a string of type (DD/MM/YYYY) into a Date type structure
 * 
 * @param date_str [in] string to be parsed into Date
 * @param date [out] address of variable of type PtDate to hold the generated Date
 */
void parseDate(char *date_str, PtDate *date);

/**
 * @brief Case insensitive string comparison
 * 
 * @param str1 [in] first string 
 * @param str2 [in] second string
 * 
 * @return int 0 if str1 equals str2 or,
 * @return int !0 if both strings are not equal
 */
int equalsStringIgnoreCase(char str1[], char str2[]);

/**
 * @brief Clears all data in memory allocated by this program to 'list' and 'map'
 * 
 * @param list [in] list of patients to be destroyed
 * @param map [in] map of regions to be destroyed
 */
void clearMemory(PtList *list, PtMap *map);