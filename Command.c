/**
 * @file Command.c
 * 
 * @brief Provides an implementation for all the main commands of the project
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Command.h"
#include "lib/ADTQueue/queue.h"
#include "Patient.h"

typedef char String[255];

/**
 * @brief Structure helper for 'top5' function
 * Stores a patient's id and his respective recovery time
 */
typedef struct recovery{
    long int id;        // patients id
    int recoveryDays;   // patient's recovery time in days
    int age;            // patient's age
} Recovery;

/**
 * @brief Helper function. Calculates days with illness of a given patient.
 * 
 * Is patient is still isolated, it calculates using the most recent confirmed date in given 'list'
 * 
 * @param list [in] list with patients
 * @param patient [in] patient to calculate days with illness
 * @param total [out] total of days with illness of 'patient'
 */
static void calculateDaysWithIllness(PtList list, PtPatient patient, int *total)
{
    int size;
    listSize(list, &size);

    // Deceased
    if(!dateIsEmpty(patient->ptDeceasedDate))
    {
        *total = dateSubtract(patient->ptConfirmedDate, patient->ptDeceasedDate);
    }
    // Released
    else if(!dateIsEmpty(patient->ptReleaseDate))
    {
        *total = dateSubtract(patient->ptConfirmedDate, patient->ptReleaseDate);
    }
    // Isolated
    else
    {
        /**
         * As these patients are isolated, this is picking the most recent confirmedDate
         * and using it for counting days with illness
         */
        PtDate recent = NULL;
        PtPatient temp_patient = NULL;
        for(int i = 0; i < size; i++)
        {
            listGet(list, i, &temp_patient);

            if(recent == NULL) recent = temp_patient->ptConfirmedDate; 
            else if(dateSubtract(recent, temp_patient->ptConfirmedDate) > 0)
            {
                recent = temp_patient->ptConfirmedDate;
            }
        }
        *total = dateSubtract(patient->ptConfirmedDate, recent);
    }
}

/**
 * @brief Helper function. Swaps values between two recovery structures
 * 
 * @param r1 [in] first recovery structure
 * @param r2 [in] second recovery structure
 */
static void swapRec(Recovery *r1, Recovery *r2)
{
    Recovery temp = *r1;
    *r1 = *r2;
    *r2 = temp;
}

/**
 * @brief Helper function. Sorts an array 'arr' in descending order using bubble sort algorithm
 * 
 * @param arr [in] recovery array to be ordered
 * @param size [in] size of 'arr'
 */
static void recoverySort(Recovery *arr, int size)
{
    for(int i = 0; i < size - 1; i++)
    {
        for(int j = 0; j < size - i - 1; j++)
        {
            // Order days
            if(arr[j].recoveryDays < arr[j + 1].recoveryDays)
            {
                swapRec(&arr[j], &arr[j + 1]);
            }
            // Order ages
            else if(arr[j].recoveryDays == arr[j + 1].recoveryDays)
            {
                if(arr[j].age < arr[j + 1].age)
                    swapRec(&arr[j], &arr[j + 1]);
            }
        }
    }
}

/**
 * @brief Helper function. Prints one line worth of a given 'patient' information
 * 
 * @param patient [in] patient to print
 */
static void printPatientOneLine(PtPatient patient)
{
    printf("SEX: %s, AGE: %d, COUNTRY/REGION: %s/%s, STATE: %s",
        patient->sex, (patient->birthYear > 0) ? 2020 - patient->birthYear : -1, 
        patient->country, patient->region, patient->status);
}

/**
 * @brief Helper function. Fetches, by reference, a patient from list given it's ID
 * 
 * @param list [in] list with patients
 * @param list_size [in] size of 'list' 
 * @param id [in] id of patient to fetch
 * @param patient [out] pointer to patient to store value.
 */
static void getPatient(PtList list, int list_size, long int id, PtPatient *patient)
{
    for(int i = 0; i < list_size; i++)
    {
        listGet(list, i, patient);
        if((*patient)->id == id) return;
    }

    *patient = NULL;
}

/**
 * @brief Checks if a region is infected, which means it has at least one isolated patient
 * 
 * @param region [in] name of the region to check
 * @param list   [in] list of patients to look through
 * 
 * @return true if region is infected or, 
 * @return false if region is clean
 */
static bool isRegionInfected(char *region, PtList list)
{
    int size;
    listSize(list, &size);

    PtPatient patient = NULL;
    for(int i = 0; i < size; i++)
    {
        listGet(list, i, &patient);
        if(strcmp(region, patient->region) == 0 && 
            strcmp("isolated", patient->status) == 0) 
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Orders alphabetically a given list of PtRegions
 * 
 * @param regions_list [in] list of 'ptRegions'
 * @param list_size [in] size of 'regions_list'
 */
static void orderRegionsList(PtRegion *regions_list, int list_size)
{
    PtRegion temp = NULL;
    for(int i = 0; i < list_size-1; i++)
    {
        for(int j = i + 1; j < list_size; j++)
        {
            if(strcmp(regions_list[i]->name, regions_list[j]->name) > 0)
            {
                temp = regions_list[i];
                regions_list[i] = regions_list[j];
                regions_list[j] = temp;
            }
        }
    }
}

/**
 * @brief Helper function for 'oldest' command. Prints queue in a format specific to this context
 * 
 * @param queue [in] queue with ids of patients elements to print
 * @param list  [in] list with patients to match with the id's in queue
 * @param sex   [in] title to print before the queue is printed
 */
static void printOldest(PtQueue queue, PtList list, char *sex)
{
    printf("%s:\n", sex);

    int size;
    listSize(list, &size);

    long int id;
    PtPatient patient = NULL;
    while(!queueIsEmpty(queue))
    {
        queueDequeue(queue, &id);
        getPatient(list, size, id, &patient);
        printf("ID: %ld, ", id);
        printPatientOneLine(patient);
        printf("\n");
    }
}

/**
 * @brief Helper function for 'oldest' command. Adds id to queue if it's respective patient is older.
 * 
 * This function mostly serves for removing code duplication 
 * 
 * @param queue [in] queue with patient ids
 * @param age [in] age of current patient id
 * @param oldest [in] current oldest age found
 * @param id [in] id of current patient 
 */
static void helpOldest(PtQueue queue, int age, int *oldest, long int id)
{
    if(age > *oldest)
    {
        queueClear(queue);
        *oldest = age;
        queueEnqueue(queue, id);
    }
    else if(age == *oldest)
    {
        queueEnqueue(queue, id);
    }
}

/**
 * @brief Calculates mortality, lethality and incident rate of a given region.
 * 
 * Returns out parameters as -1 if there's not enough population data
 * 
 * @param region [in] pointer to region
 * @param list [in] pointer to list with patients
 * @param lethality [out] pointer to store lethality rate 
 * @param mortality [out] pointer to store mortality rate
 * @param incident_rate [out] pointer to store incident rate
 */
static void stats(PtRegion region, PtList list, float *lethality, float *mortality, float *incident_rate)
{
    bool skip = false; // checks if there's enough data 
    int size; 
    float cases = 0, deaths = 0;
    listSize(list, &size);
    
    PtPatient patient = NULL;
    for(int i = 0; i < size; i++)
    {
        listGet(list, i, &patient);
        if(strcmp(region->name, patient->region) != 0) continue;
        cases++;
        if(strcmp(patient->status, "deceased") == 0) deaths++;
    }
    if(cases == 0) return;
    
    *lethality = (deaths / cases) * 100.00;
    *mortality = (deaths / region->population) * 10000.00;
    *incident_rate = (cases / region->population) * 100.00;
}

void printCommandsMenu() 
{
	printf("\n===================================================================================");
	printf("\n                          PROJECT: COVID-19                    ");
	printf("\n===================================================================================");
	printf("\nA. Base Commands (LOADP, LOADR,CLEAR).");
	printf("\nB. Simple Indicators and searchs (AVERAGE, FOLLOW, MATRIX, OLDEST, GROWTH, SEX, SHOW, TOP5).");
	printf("\nC. Advanced indicator (REGIONS, REPORTS)");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}

void loadPatients(PtList *patient_list)
{
    // Check if patients are already loaded into list
    if(*patient_list != NULL)
    {
        printf("Patients already loaded!\n");
        return;
    }

    // Get file name
    String file_name;
    printf("FILE NAME: ");
    fgets(file_name, sizeof(file_name), stdin);
    file_name[strlen(file_name)-1]='\0'; // removes line break at the end of string

    // Create list
    int size;
    int err = countEntries(file_name, &size);
    if(err == UTIL_FILE_NULL)
    {
        printf("Error loading patients: %d!\n", err);
        return;
    }
    
    *patient_list = listCreate(size);

    // Load patients
    loadPatientsIntoList(file_name, *patient_list);
}

void loadRegions(PtMap *region_map)
{
    // Check if regions are already loaded into map
    if(*region_map != NULL)
    {
        printf("Regions already loaded!\n");
        return;
    }

    // Get file name
    String file_name;
    printf("FILE NAME: ");
    fgets(file_name, sizeof(file_name), stdin);
    file_name[strlen(file_name)-1]='\0'; // removes line break at the end of string

    // Create map
    int size;
    int err = countEntries(file_name, &size);
    if(err == UTIL_FILE_NULL)
    {
        printf("Error loading regions: %d!\n", err);
        return;
    }

    *region_map = mapCreate(size);

    // Load regions
    loadRegionIntoMap(file_name, *region_map);
}

void matrix(PtList list)
{
    if(list == NULL) return;

    int matrix[6][3] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    bool confirmed, deceased, released;

    int size, age, total = 0, col;
    listSize(list, &size);

    PtPatient patient = NULL;
    for(int i = 0; i < size; i++)
    {
        listGet(list, i, &patient);
        
        if(patient->birthYear == -1) continue;
        total++; // total patients with birth year
        age = 2020 - patient->birthYear;

        confirmed = strcmp(patient->status, "isolated") == 0;
        deceased  = strcmp(patient->status, "deceased") == 0;
        released  = strcmp(patient->status, "released") == 0;
        
        switch(age)
        {
            case 0  ... 15: col = 0; break;
            case 16 ... 30: col = 1; break;
            case 31 ... 45: col = 2; break;
            case 46 ... 60: col = 3; break;
            case 61 ... 75: col = 4; break;
            default: col = 5; break;
        }

        // Fill matrix
        if(confirmed) matrix[col][0]++;
        else if(deceased) matrix[col][1]++;
        else if(released) matrix[col][2]++;
    }

    char ages[7][9] = {"[ 0-15]", "[16-30]", "[31-45]", "[46-60]", "[61-75]", "[76...]"};

    // Print matrix
    printf("\n+------------------------------+\n");
    printf("|   %d  | cmfd | dcsd | rlsd |", total);
    printf("\n+------------------------------+\n");
    for(int i = 0; i < 6; i++)
    {
        printf("| %s ", ages[i]);
        for(int j = 0; j < 3; j++)
        {
            printf("| %4d ", matrix[i][j]);
        }
        printf("|\n");
    }
    printf("+------------------------------+\n");
    printf("| [TOTAL] ");
    for(int i = 0; i < 3; i++)
    {
        int total = 0;
        for(int j = 0; j < 6; j++)
        {
            total += matrix[j][i];
        }
        printf("| %4d ", total);
    }
    printf("|\n+------------------------------+\n");
}

void show(PtList list, long int id)
{
    if(list == NULL) return;
    
    int size, infected_days;
    listSize(list, &size);

    PtPatient patient = NULL;
    for(int i = 0; i < size; i++)
    {
        listGet(list, i, &patient);
        if(patient->id == id) break;
    }
    if(patient == NULL) return;

    calculateDaysWithIllness(list, patient, &infected_days);

    printf("\nID: %ld\nSEX: %s\nAGE: %d\nCOUNTRY/REGION: %s/%s \nINFECTED REASION: %s\nSTATE: %s\nNUMBER OF DAYS WITH ILLNESS: %d\n",
    patient->id, patient->sex, (patient->birthYear > 0) ? 2020 - patient->birthYear : -1, 
    patient->country, patient->region, patient->infectionReason, patient->status, infected_days);
}

void sex(PtList list)
{
    if(list == NULL) return;

    int size, male = 0, female = 0, unknown = 0;
    char sex[6];
    listSize(list, &size);

    PtPatient patient = NULL;
    for(int i = 0; i < size; i++)
    {
        listGet(list, i, &patient);
        
        if(strcmp(patient->sex, "male") == 0) male++;
        else if(strcmp(patient->sex, "female") == 0) female++;
        else  unknown++;
    }

    female = round((float)(female * 100) / size);
    male =  round((float)(male * 100) / size);
    unknown = round((float)(unknown * 100) / size);

    printf("Percentage of Females: %d%%\nPercentage of Males: %d%%\nPercentage of Unknown: %d%%\nTotal of Patients %d\n", female, male, unknown, size);
}

void average(PtList list)
{
    int total_deceased_age = 0, total_released_age = 0, total_isolated_age = 0;
    int count_deceased = 0, count_released = 0, count_isolated = 0;

    int size, age;
    listSize(list, &size);

    PtPatient patient = NULL;
    for(int i = 0; i < size; i++)
    {
        listGet(list, i, &patient);
        if(patient->birthYear == -1) continue;

        age = (2020 - patient->birthYear);
        if(strcmp(patient->status, "deceased") == 0)
        {
            total_deceased_age += age;
            count_deceased++;
        }
        else if(strcmp(patient->status, "released") == 0)
        {
            total_released_age += age;
            count_released++;
        }
        else if(strcmp(patient->status, "isolated") == 0)
        {
            total_isolated_age += age;
            count_isolated++;
        }
    }

    printf("Average Age for deceased patients: %d\nAverage Age for released patients: %d\nAverage Age for isolated patients: %d\n",
       (int)round((float)total_deceased_age/count_deceased), (int)round((float)total_released_age/count_released), (int)round((float)total_isolated_age/count_isolated));
}

void top(PtList list)
{
    if(list == NULL) return;
    Recovery top[5];
    
    int size, daysIllness, age, index = 0;
    listSize(list, &size);

    PtPatient patient = NULL;
    for(int i = 0; i < size; i++)
    {
        listGet(list, i, &patient);
        if(dateIsEmpty(patient->ptReleaseDate)) continue;

        calculateDaysWithIllness(list, patient, &daysIllness);
        age = 2020 - patient->birthYear;
        Recovery rec = {patient->id, daysIllness, age};

        // Fill top array with first values found
        if(index < 5)
        { 
            top[index++] = rec; 
            continue; 
        }
        
        recoverySort(top, 5);

        // Add top 5 recovers to array, creating a desordered array with all top values
        for(int i = 4; i >= 0; i--)
        {
            if(top[i].recoveryDays < rec.recoveryDays)
            {
                top[i] = rec;
                break;
            }
        }
    }
    recoverySort(top, 5);
    for(int i = 0; i < 5; i++) show(list, top[i].id);
}

void growth(PtList list, PtDate date)
{
    if(list == NULL) return;
    if(date == NULL) return;

    PtDate previousDate = NULL;
    datePrevious(date, &previousDate);
    
    int size;
    listSize(list, &size);

    int isolated = 0, deceased = 0;
    int isolated_prev = 0, deceased_prev = 0;

    PtPatient patient = NULL;
    for(int i = 0; i < size; i++)
    {
        listGet(list, i, &patient);

        if(dateEqual(date, patient->ptDeceasedDate)) deceased++;
        if(dateEqual(date, patient->ptConfirmedDate)) isolated++;
        if(dateEqual(previousDate, patient->ptDeceasedDate)) deceased_prev++;
        if(dateEqual(previousDate, patient->ptConfirmedDate)) isolated_prev++;
    }


    if(isolated == 0 && deceased == 0) 
    {
        printf("\nTheres is no record for day "); 
        datePrint(date);
        return;
    }

    printf("\nDate: "); datePrint(previousDate);
    printf("\nNumber of dead: %i\nNumber of isolated:%i\n", deceased_prev, isolated_prev);
    printf("\nDate: "); datePrint(date);
    printf("\nNumber of dead: %i\nNumber of isolated:%i\n", deceased, isolated);
    printf("\nRate of new infected:  %d%%\n",  (int)round((float)((isolated - isolated_prev) * 100) / ((isolated_prev == 0) ? 1 : isolated_prev) ));
    printf("Rate of new deceased:  %d%%",      (int)round((float)((deceased - deceased_prev) * 100) / ((deceased_prev == 0) ? 1 : deceased_prev) ));

    dateDestroy(&previousDate);
}

void follow(PtList list, long int id)
{
    if(list == NULL) return;


    int size;
    listSize(list, &size);
    // Get main patient
    PtPatient patient = NULL;
    getPatient(list, size, id, &patient);
    if(patient == NULL)
    {
        printf("Patient not found!\n");
        return;
    }
    
    printf("Following Patient: ID: %ld, ", patient->id);
    printPatientOneLine(patient);

    long int infectedBy = patient->infectedBy;
    do
    {
        if(infectedBy == -1)
        {
            printf("\nContaminated by Unknown");
            return;
        }

        printf("\nContaminated by Patient: ID: ");
        for(int i = 0; i < size; i++)
        {
            listGet(list, i, &patient);
            if(patient->id == infectedBy)
            {
                printf("%ld, ", patient->id);
                printPatientOneLine(patient);
                infectedBy = patient->infectedBy;
                break;
            }
            patient = NULL;
        }
    }while(patient != NULL);
    printf("%ld : doest not exist record\n", infectedBy);
}

void oldest(PtList list)
{
    if(list == NULL) return;

    int oldest_age_male = 0, oldest_age_female = 0;

    PtQueue oldest_male = queueCreate(5);
    queueEnqueue(oldest_male, 0);
    PtQueue oldest_female = queueCreate(5);
    queueEnqueue(oldest_female, 0); 

    int size, age;
    listSize(list, &size);

    PtPatient patient = NULL;
    for(int i = 0; i < size; i++)
    {
        listGet(list, i, &patient);
        if(patient->birthYear == -1) continue;

        age = 2020 - patient->birthYear;

        if(strcmp(patient->sex, "male") == 0)
            helpOldest(oldest_male, age, &oldest_age_male, patient->id);
        else if(strcmp(patient->sex, "female") == 0)
            helpOldest(oldest_female, age, &oldest_age_female, patient->id);
    }

    printOldest(oldest_female, list, "FEMALE");
    printOldest(oldest_male, list, "MALE");

    queueDestroy(&oldest_female);
    queueDestroy(&oldest_male);
}

void regions(PtList list, PtMap map)
{
    if(list == NULL) return;
    if(map == NULL) return;

    int size_map, list_size, regions_index = 0;
    mapSize(map, &size_map);

    MapKey *keys = mapKeys(map);

    PtRegion regions[size_map]; // Holds infected reagions
    PtRegion region = NULL;     // Holds current region in loop
    
    for(int i = 0; i < size_map; i++)
    {
        mapGet(map, keys[i], &region);
        if(isRegionInfected(region->name, list))
        {
            regions[regions_index++] = region;
        }
    }
    free(keys);
    
    orderRegionsList(regions, regions_index - 1);

    printf("<%d infected regions>\n", regions_index);
    for(int i = 0; i < regions_index; i++)  regionPrint(regions[i]); 
}

void report(PtList list, PtMap map)
{
    if(list == NULL) return;
    if(map == NULL) return;

    float lethality = -1, mortality = -1, incident_rate = -1;
    int size_map, total = 1;
    mapSize(map, &size_map);

    MapKey *keys = mapKeys(map);
    PtRegion region = NULL; // Holds current region in loop
    
    for(int i = 0; i < size_map; i++)
    {
        mapGet(map, keys[i], &region);
        stats(region, list, &lethality, &mortality, &incident_rate);

        printf("\n <%2d> REGION: %s | ", total++, region->name);

        (incident_rate == -1) ? // If any the values are -1, there was no population data
        printf("Unknown (no population data)") :
        printf("Mortality: %f%% Incident Rate: %f%% Lethality: %f%%", mortality, incident_rate, lethality);
        printf("\n");
    }
    free(keys);
}