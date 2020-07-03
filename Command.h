/**
 * @file Command.h
 * 
 * @brief Defines the signature for all the main commands of the project
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#pragma once

#include "lib/ADTList/list.h"
#include "lib/ADTMap/map.h"

#include "Utils.h"

/**
 * @brief Clears all data in memory allocated by this program to 'list' and 'map'
 * 
 * @param list [in] list of patients to be destroyed
 * @param map [in] map of regions to be destroyed
 */
void clearMemory(PtList *list, PtMap *map);

/**
 * @brief Prints the main menu of the project
 */
void printCommandsMenu();

/**
 * @brief Loads patients into list. File name will be prompt to user
 * 
 * @param patient_list [in] list type with NULL address
 */
void loadPatients(PtList *patient_list);

/**
 * @brief Loads regions into map. File name will be prompt to user
 * 
 * @param region_map [in] map type with NULL address
 */
void loadRegions(PtMap *region_map);

/**
 * @brief Prints a 6x3 integer Matrix that links age group with confirmed, deceased and released patients.
 * 
 * This function assumes age from year 2020, as in (year = 2020 - birthYear). 
 * Patients without birthDate will not be counted
 * 
 * @param list [in] list filled with patients
 */
void matrix(PtList list);

/**
 * @brief Prints data of a patient with id of 'id'
 * 
 * @param list [in] list with patients
 * @param id [in] id of patient to fetch
 */
void show(PtList list, long int id);

/**
 * @brief Prints percentages about gender in given list
 * 
 * @param list [in] list with patients
 */
void sex(PtList list);

/**
 * @brief Prints average age of each type of patient (deceased, released and isolated)
 * 
 * @param list [in] list with patients
 */
void average(PtList list);

/**
 * @brief Prints, in descending order, patients that took the longest to recover.
 * This function IGNORES patients with "isolated" and "deceased" status
 * 
 * @param list [in] list with patients
 */
void top(PtList list);

/**
 * @brief Given a date, shows the rate of growth of deaths and infections compared to the previous day
 * 
 * @param list [in] list with patients
 * @param date [in] date to get growth from
 */
void growth(PtList list, PtDate date);

/**
 * @brief Prints the sequence of infections of a given patients E.g. A infected by B, B infected by D ...
 * 
 * @param list [in] list with patients
 * @param id [in] id of patient to follow
 */
void follow(PtList list, long int id);

/**
 * @brief Prints the oldest patient of each sex.
 * 
 * @param list [in] list with patients
 */
void oldest(PtList list);

/**
 * @brief Prints, in alphabetic order, the list of regions with still infected patients 
 * 
 * @param list [in] list with patients
 * @param map  [in] map with regions
 */
void regions(PtList list, PtMap map);

/**
 * @brief Creates a .txt file, in the same directory, with lethality, mortality and incident rates 
 * 
 * @param list [in] list with patients
 * @param map  [in] map with regions
 */
void report(PtList list, PtMap map);