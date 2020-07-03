/**
 * @file Region.h
 * 
 * @brief Defines the type PtRegion and associated operations.
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#pragma once

#define REGION_OK   0
#define REGION_NULL 1

/**
 * @brief Structure that defines a region
 */
typedef struct regionImpl {
    char name[40];     
    char capital[40];  
    float area;  
    int population;
} Region;

/** Definition of a pointer to the region data structure */
typedef struct regionImpl *PtRegion;

/**
 * @brief Creates a new Region
 * 
 * @param name [in] of the region
 * @param capital [in] of the region
 * @param area [in] of the region
 * @param population [in] of the region
 * 
 * @return PtRegion pointer to allocated data structure, or
 * @return NULL if memory allocation was not possible 
 */
PtRegion regionCreate(char *name, char *capital, float area, int population);

/**
 * @brief Free all resources associated with '*ptRegion'
 * 
 * @param ptRegion [in] ADDRESS of pointer to the region
 *  
 * @return REGION_OK if success, or
 * @return REGION_NULL if '*ptRegion' is NULL
 */
int regionDestroy(PtRegion *ptRegion);

/**
 * @brief Prints a meaningful representation of a region
 * 
 * @param ptDate [in] pointer to the region
 */
void regionPrint(PtRegion ptRegion);

/**
 * @brief Creates a copy of 'original' into 'copy'. Allocates all resources necessary
 * 
 * @param original [in] original region to be copied
 * @param copy [out] file to put the copy in
 */
void regionCopy(PtRegion original, PtRegion *copy);