/**
 * @file testDate.c
 * 
 * @brief This is a test for Date Module, to ensure no memory leaks and all operations are working as expected. This test is meant to run with valgrind
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#include <stdlib.h>
#include <stdio.h>
#include "../Date.h"

void testDateCreate();
void testDatePrint();

int main()
{
    testDateCreate();
    testDatePrint();
}

/**
 * @brief This tests the function 'dateCreate'
 * 
 * Should only create the first date, since the last two are invalid
 * Should have no memory leaks, since only one date was created, only one needs to be destroyed
 * Valgrind should return no errors
 * 
 */
void testDateCreate()
{
    PtDate date  = dateCreate(14, 5, 1997);
    PtDate date1 = dateCreate(32, 5, 1997);   // Invalid day
    PtDate date2 = dateCreate(14, 13, 1997);  // Invalid month

    dateDestroy(&date);
}

/**
 * @brief This tests the function 'datePrint'
 * 
 * Should print a valid date, using the format DD/MM/YYYY
 * Should have no memory leaks, since only one date was created, only one needs to be destroyed
 * Valgrind should return no errors
 * 
 */
void testDatePrint()
{
    PtDate date  = dateCreate(14, 5, 1997);
    PtDate date1 = dateCreate(32, 5, 1997);   // Invalid date

    datePrint(date);
    datePrint(date1);

    printf("\n");

    dateDestroy(&date);
}