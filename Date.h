/**
 * @file Date.h
 * 
 * @brief Defines the type PtDate and associated operations.
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#pragma once

#include <stdbool.h>

#define DATE_OK   0
#define DATE_NULL 1

/** Forward declaration of the date data structure */
struct dateImpl;

/** Definition of a pointer to the date data structure */
typedef struct dateImpl *PtDate;

/**
 * @brief Creates a new date type
 * 
 * @param day [in] represents day of the year
 * @param month [in] represents month of the year
 * @param year [in] represents a year
 * 
 * @return PtDate pointer to allocated data structure, or
 * @return NULL if memory allocation was not possible 
 */
PtDate dateCreate(unsigned int day, unsigned int month, unsigned int year);

/**
 * @brief Free all resources associated with '*ptDate'
 * 
 * @param ptDate [in] ADDRESS of pointer to the date 
 * 
 * @return DATE_OK if success, or
 * @return DATE_NULL if '*ptDate' is NULL
 */
int dateDestroy(PtDate *ptDate);

/**
 * @brief Prints a meaningful representation of a date, using the following format: DD/MM/YYYY
 * 
 * @param ptDate [in] pointer to the date
 */
void datePrint(PtDate ptDate);

/**
 * @brief Checks if a given 'ptDate' is (0/0/0), which is the default value empty dates.
 * 
 * @param ptDate [in] Pointer to date to be check
 * 
 * @return true is empty (0/0/0) or,
 * @return false is not empty and represents a valid Date
 */
bool dateIsEmpty(PtDate ptDate);

/**
 * @brief Subtracts two dates and returns number of days. Make sure the first param is the oldest date
 * 
 * For this context, we assume all dates are from 2020
 * 
 * @param ptDate_old [in] oldest date
 * @param ptDate_new [in] most recent date
 * 
 * @return int number of days resultant from subtraction 
 */
int dateSubtract(PtDate ptDate_old, PtDate ptDate_new);


/**
 * @brief Compares if two dates are equal
 * 
 * For this context, we assume all dates are from 2020
 * 
 * @param ptDate_first [in] First date
 * @param ptDate_second [in] Second date
 * 
 * @return int number of days resultant from subtraction 
 */
bool dateEqual(PtDate ptDate_first, PtDate ptDate_second);


/**
 * @brief Get previous day of a given date. For this context, we assume all dates are from 2020
 * 
 * @param ptDate [in] date
 * @param previous [out] date prior to 'ptDate_first'
 */
void datePrevious(PtDate ptDate, PtDate *previous);


