/**
 * @file testRegion.c
 * 
 * @brief This is a test for the Region module, to ensure no memory leaks and all operations are working as expected. This test is meant to run with valgrind
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#include <stdlib.h>
#include <stdio.h>
#include "../Region.h"

void testRegionCreatePrintDestroy();

int main()
{
    testRegionCreatePrintDestroy();
}

/**
 * @brief This tests three functions: 'regionCreate', 'regionPrint' and 'regionDestroy'
 * 
 * This creates a valid region
 * Should be printed
 * All resources should be properly disposed
 * Valgrind shoudl return no errors
 * 
 */
void testRegionCreatePrintDestroy()
{
    PtRegion region = regionCreate("RegionName", "RegionCapital", 666.66, 9999999);
    regionPrint(region);
    regionDestroy(&region);
}