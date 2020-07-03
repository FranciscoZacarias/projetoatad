/**
 * @file mapElem_region.h
 * 
 * @brief Defines the types MapKey and MapValue
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#pragma once

#include <stdbool.h>
#include "../../Region.h"

/** Key type definition */
typedef char* MapKey;

/** Value type definition */
typedef PtRegion MapValue;

/**
 * @brief Prints a key.
 * 
 * Must be implemented according concrete
 * type of MapKey.
 * 
 * @param key [in] key to print
 */
void mapKeyPrint(MapKey key);

/**
 * @brief Prints a value.
 * 
 * Must be implemented according concrete
 * type of MapValue.
 * 
 * @param value [in] value to print
 */
void mapValuePrint(MapValue value);

/**
 * @brief Compares two keys for equality.
 * 
 * This function is used by the ADT Map to perform
 * a key-based access to the underlying data.
 * 
 * @param key1 [in] a key
 * @param key2 [in] another key
 * 
 * @return 'true' if keys match, or
 * @return 'false' if keys don't match. 
 */
bool mapKeyEquals(MapKey key1, MapKey key2);
