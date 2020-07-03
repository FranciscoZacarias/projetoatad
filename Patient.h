/**
 * @file Patient.h
 * 
 * @brief Defines the type PtPatient and associated operations.
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#pragma once

#define PATIENT_OK   0
#define PATIENT_NULL 1

#include "Date.h"
#include "Region.h"

/**
 * @brief Structure that defines a patient and his status information
 */
typedef struct patientImpl{
    long int id;
    char sex[6];            // {“male”, “female”}
    int birthYear;
    char country[40];
    char region[40];
    char infectionReason[100]; 
    long int infectedBy;    // id of the infected patient, -1 if no one
    PtDate ptConfirmedDate;
    PtDate ptReleaseDate;
    PtDate ptDeceasedDate;
    char status[10];        // {“isolated, “released”, “deceased”}
} Patient;

/** Definition of a pointer to the patient data structure */
typedef struct patientImpl *PtPatient;

/**
 * @brief Create a new Patient 
 * 
 * This functions assumes data integrity, as in all parameters must have been 
 * properly parsed before creating a patient, as this functions makes no internal
 * parsing or input verification.
 * 
 * @param id [in] patient's id
 * @param sex [in] gender ("male" or "female")
 * @param birthYear [in] birth year
 * @param country [in] birth country
 * @param region [in] patient's region
 * @param infectionReason [in] reason why patient got infected
 * @param infectedBy [in] patient's id that infected this patient
 * @param confirmedDate [in] pointer to Date of confirmed infection
 * @param releaseDate [in] pointer to Date of release date
 * @param deceaseDate [in] pointer to Date of decease date
 * @param status [in] patient statys ("isolated", "released", "deceased")
 * 
 * @return PtPatient if success, or
 * @return NULL if memory allocation was not possible 
 */
PtPatient patientCreate(long int id, char *sex, int birthYear, char *country, char *region, char *infectionReason,
            long int infectedBy, PtDate confirmedDate, PtDate releaseDate, PtDate deceaseDate, char *status);

/**
 * @brief Free all resources associated with '*ptPatient'
 * 
 * @param ptPatient [in] ADDRESS of pointer to 'patient'
 * 
 * @return int PATIENT_OK if success, or
 * @return int PATIENT_NULL if '*ptPatient' is NULL
 */
int patientDestroy(PtPatient *ptPatient);

/**
 * @brief Prints a meaningful representation of a patient
 * 
 * @param ptPatient [in] pointer to the patient
 */
void patientPrint(PtPatient ptPatient);