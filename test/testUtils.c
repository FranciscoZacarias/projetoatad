/**
 * @file testUtil.c
 * 
 * @brief This is a test for the Util module, to ensure no memory leaks and all operations are working as expected. This test is meant to run with valgrind
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#include <stdlib.h>
#include <stdio.h>
#include "../Utils.h"
#include "../Patient.h"
#include "../lib/ADTList/list.h"
#include "../lib/ADTMap/map.h"

#define REGIONS_PATH "regions.csv"
#define PATIENTS_PATH "patients.csv"

void testLoadRegionIntoMap();
void testPatientsIntoList();
void testCountEntries();
void testRemoveChar();
void testParseDate();

int main()
{
    testLoadRegionIntoMap();
    testPatientsIntoList();
    testCountEntries();
    testRemoveChar();
}

/**
 * @brief This tests the function 'loadRegionIntoMap' 
 * 
 * Should fill 18 entries in the created map (skips header line)
 * Map should be of size 19 (since it counts header line)
 * Should get the region requested by the key 'South Korea'
 * Should be destroyed in the end
 * Valgrind should return no errors
 * 
 */
void testLoadRegionIntoMap()
{
    // Create map
    int region_entries;
    countEntries("regions.csv", &region_entries);
    PtMap map = mapCreate(region_entries);

    PtRegion region;
    
    loadRegionIntoMap(REGIONS_PATH, map);
    mapGet(map, "South Korea", &region);

    destroyStringRegionMap(&map);

    /**
     * Here we don't destroy 'region' because that pointer
     * will be destroyed when map is destroyed
     */
}
/**
 * @brief This tests the function 'loadPatientsIntoList'
 * 
 * Should populate list with all patients
 * Should destroy all patients in list and list aswell
 * Valgrind should return no errors
 * 
 */
void testPatientsIntoList()
{
    int patient_entries;
    countEntries("patients.csv", &patient_entries);
    PtList list = listCreate(patient_entries);

    // Populates list with patients
    loadPatientsIntoList(PATIENTS_PATH, list);

    destroyPatientList(&list);
}

/**
 * @brief This tests the function 'countEntries'
 * 
 * Should count 19 entries in regions.csv file (since it also counts the header line)
 * Valgrind should return no errors
 * 
 */
void testCountEntries()
{
    int lines;
    countEntries(REGIONS_PATH, &lines);
    printf("\nCountEntries: %d\n", lines);
}

/**
 * @brief This tests the function 'removeChar'
 * 
 * Should remove all commas from char and return the numbers 1 to 9
 * Valgrind should return no errors
 * 
 */
void testRemoveChar()
{
    char myStr[] = "1,2,3,4,5,6,7,8,9";
    removeChar(myStr, ',');
    printf("RemoveChar: %s\n", myStr);
}