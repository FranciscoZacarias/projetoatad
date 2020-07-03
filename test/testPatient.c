/**
 * @file testPatient.c
 * 
 * @brief This is a test for Patient Module, to ensure no memory leaks and all operations are working as expected. This test is meant to run with valgrind
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#include <stdlib.h>
#include <stdio.h>

#include "../Patient.h"
#include "../Date.h"
#include "../Region.h"

void testCreatePrintDestroy();

int main()
{
    testCreatePrintDestroy();
}

/**
 * @brief This tests three functions: 'patientCreate', 'patientPrint' and 'patientDestroy'
 * 
 * Should create one patient 
 * Should print said patient
 * Should free all allocated resources 
 * Valgrind should return no errors 
 * 
 */
void testCreatePrintDestroy()
{
    PtDate confirmedDate = NULL; // dateCreate(20, 8, 2018);
    PtDate releaseDate = dateCreate(28, 9, 2018);
    PtDate deceasedDate = dateCreate(11, 9, 2018);
    
    PtPatient patient = patientCreate(1, "male", 1997, "Portugal", "Lisbon", "Shaked hands with the CEO of corona",
                -1, confirmedDate, releaseDate, deceasedDate, "isolated");

    patientPrint(patient);
    patientDestroy(&patient);
}