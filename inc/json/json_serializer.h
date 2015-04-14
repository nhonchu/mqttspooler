/*
 * json_serializer.h
 *
 *  Created on: Apr 24, 2014
 *      Author: rjacolin
 *
 *  Modified on March 2015, nhonchu
 *      changed timestamps from int* to unsigned long*
 *
 */

#ifndef JSON_SERIALIZER_H_
#define JSON_SERIALIZER_H_

char* json_valueList(char* buffer, unsigned long* timestamps, char** values, int nbOfValues);
char* json_data(char* buffer, char* name, unsigned long* timestamps, char** values, int nbOfValues);
char* json_encapsulate(char* payload);

#endif /* JSON_SERIALIZER_H_ */
