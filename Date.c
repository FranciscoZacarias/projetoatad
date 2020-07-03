/**
 * @file Date.c
 * 
 * @brief Provides an implementation of the Date data structure
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#include <stdlib.h>
#include <stdio.h>

#include "Date.h"

/**
 * @brief Structure that defines a date using the format DD/MM/YYYY
 */
typedef struct dateImpl {
    unsigned int day;
    unsigned int month;
    unsigned int year;
} Date;

/**
 * @brief Helper function for 'dateSubtract'
 * 
 * @param size [in] month of the year E.g. 4, as in April
 * @param total [out] total of days of each month, except current 
 */
static void loopMonth(int size, int *total)
{
    int days, i;
    for(i = 1; i < size; i++)
    {
        if(i == 2) days = 29; // February
        if(i % 2 == 0) days = 30;
        else days = 31;

        *total += days;
    }
}

PtDate dateCreate(unsigned int day, unsigned int month, unsigned int year)
{
    if (day > 31) return NULL;
    if (month > 12) return NULL;

    PtDate date = (PtDate)malloc(sizeof(Date));
    if (date == NULL) return NULL;

    date->day = day;
    date->month = month;
    date->year = year;
    
    return date;
}

int dateDestroy(PtDate *ptDate)
{
    PtDate date = *ptDate;
    if (date == NULL) return DATE_NULL;

    free(date);

    *ptDate = NULL;

    return DATE_OK;
}

void datePrint(PtDate ptDate)
{
    if(ptDate == NULL) 
    {
        printf("(DATE NULL)");
        return;
    }
    printf("(%u/%u/%u)", ptDate->day, ptDate->month, ptDate->year);
}

bool dateIsEmpty(PtDate ptDate)
{
    return (ptDate->year == 0 && ptDate->month == 0 && ptDate->day == 0) ? true : false;
}

int dateSubtract(PtDate ptDate_old, PtDate ptDate_new)
{
    int days_old = 0, days_new = 0;

    loopMonth(ptDate_old->month, &days_old);
    days_old += ptDate_old->day;
    
    loopMonth(ptDate_new->month, &days_new);
    days_new += ptDate_new->day;
    

    return days_new - days_old - 1;
}


bool dateEqual(PtDate ptDate_first, PtDate ptDate_second)
{
    if(ptDate_first == NULL) return false;
    if(ptDate_second == NULL) return false;

    if(ptDate_first->day != ptDate_second->day ||
        ptDate_first->month != ptDate_second->month ||
        ptDate_first->year != ptDate_first->year) 
        return false;

    return true;
}


void datePrevious(PtDate ptDate, PtDate *previous)
{
    if(ptDate == NULL) return;

    int day = 0, month = ptDate->month;

    if(ptDate->day == 1)
    {
        month--; 
        day = 31;
        switch(ptDate->month)
        {
            case 3:
                day = 29;
                break;
            case 1: case 5: case 7: case 10: case 12:
                day = 30;
                break;
        }
    }
    else day = ptDate->day - 1;

    *previous = dateCreate(day, month, day);
}
