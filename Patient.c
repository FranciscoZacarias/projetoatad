/**
 * @file Patient.c
 * 
 * @brief Provides an implementation of the Patient data structure
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Patient.h"

PtPatient patientCreate(long int id, char *sex, int birthYear, char *country, char *region, char *infectionReason,
                long int infectedBy, PtDate confirmedDate, PtDate releaseDate, PtDate deceaseDate, char *status)
{
    PtPatient patient = (PtPatient)malloc(sizeof(Patient));
    if(patient == NULL) return NULL;

    patient->id = id;
    strcpy(patient->sex, sex);
    patient->birthYear = birthYear;
    strcpy(patient->country, country);
    strcpy(patient->region, region);
    strcpy(patient->infectionReason, infectionReason);
    patient->infectedBy = infectedBy;
    patient->ptConfirmedDate = confirmedDate;
    patient->ptReleaseDate = releaseDate;
    patient->ptDeceasedDate = deceaseDate;
    strcpy(patient->status, status); 
    
    return patient;
}

int patientDestroy(PtPatient *ptPatient)
{
    PtPatient patient = *ptPatient;
    if(patient == NULL) return PATIENT_NULL;

    dateDestroy(&(patient->ptConfirmedDate));
    dateDestroy(&(patient->ptReleaseDate));
    dateDestroy(&(patient->ptDeceasedDate));
    free(patient);

    *ptPatient = NULL;

    return PATIENT_OK;
}

void patientPrint(PtPatient ptPatient)
{
    if(ptPatient == NULL) 
    {
        printf("(PATIENT NULL)");
        return;
    }

    printf("ID: %ld | SEX: %s | BIRTH_YEAR: %d | BIRTH_COUNTRY: %s | INFECTION_REASON: %s | INFECTED_BY: %ld | STATUS: %s | REGION: %s\n",
        ptPatient->id, ptPatient->sex, ptPatient->birthYear, ptPatient->country, 
        ptPatient->infectionReason, ptPatient->infectedBy, ptPatient->status, ptPatient->region);
    printf("| CONFIRMED DATE: "); datePrint(ptPatient->ptConfirmedDate); printf("\n");
    printf("| RELEASED DATE: ");  datePrint(ptPatient->ptReleaseDate);   printf("\n");
    printf("| DECEASED DATE: ");  datePrint(ptPatient->ptDeceasedDate);  printf("\n");
}