/**
 * @file mapElem_region.c
 * 
 * @brief Implements operations for types MapKey and MapValue.
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#include <stdio.h>
#include <string.h>
#include "mapElem.h"
#include "../../Region.h"

void mapKeyPrint(MapKey key) 
{
    printf("\n%s", key);
}

void mapValuePrint(MapValue value) 
{
	regionPrint(value);
}

bool mapKeyEquals(MapKey key1, MapKey key2) 
{
	// in case of integer keys:
	return (strcmp(key1, key2) == 0); 
}