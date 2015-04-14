/*
 * json_deserializer.c
 *
 *  Created on: Jun 9, 2014
 *      Author: rjacolin
 *
 *  Modified on March 2015, nhonchu
 *		removing filtering on boolean type, all value are string type
 *
 */

#if 1
#include <malloc.h>
#else
#include <malloc/malloc.h>
#endif

#include <string.h>
#include <stdio.h>
#include "json/json_deserializer.h"
#include "json/jsmn.h"
#include "json/log.h"

char *KEYS[] = { "uid", "timestamp", "command", "id", "params" };


mqtt_data_t json_deserialize_command(jsmntok_t *tokens, char* payload, mqtt_data_t data_t);

/**
 *[{"uid":"3863fccf9a1a48af99c8bfcbf01c6b7f","timestamp":1401902872564,"command":{"id":"machine.TurnOn","params":{"Light":false}}}]
 *
 *
 * @return resultcode if negative value or number of tokens
 */
mqtt_data_t json_deserialize(char* payload)
{
	mqtt_data_t data_t;
    jsmntok_t * tokens = json_tokenise(payload);

    memset(&data_t, 0, sizeof(mqtt_data_t));

    char* temp_uid = json_token_tostr(payload, &tokens[3]);	//uid
    char* uid = BS_MEM_ALLOC(strlen(temp_uid) + 1);
    strcpy(uid, temp_uid);

    char* temp_ts = json_token_tostr(payload, &tokens[5]);	//timestamp
    char* ts = BS_MEM_ALLOC(strlen(temp_ts) + 1);
    strcpy(ts, temp_ts);

    char* temp_data = json_token_tostr(payload, &tokens[6]);
    char* data = BS_MEM_ALLOC(strlen(temp_data) + 1);
    strcpy(data, temp_data);

    if (strcmp(data, "command") == 0)
    {
    	char* temp_name = json_token_tostr(payload, &tokens[9]);
		char* name = BS_MEM_ALLOC(strlen(temp_name) + 1);
		memcpy(name, temp_name, strlen(temp_name) + 1);

		data_t.ticketId = uid;
		uid = NULL;

		data_t.timestamp = ts;
		ts = NULL;

		int max = (&tokens[11])->size;
		printf("json_deserialize - Command: %s (%d params)\r\n", name, max / 2);
		int index = 0;

		char** keys = BS_MEM_ALLOC(max / 2);

        data_t.values = (bsd_data_t *) BS_MEM_ALLOC(sizeof(bsd_data_t) * (max / 2));

		int key_index = 0;
		for(index = 0; index < max; index+=2, key_index++)
		{
			char* temp_pname = json_token_tostr(payload, &tokens[12 + index]);
			keys[key_index] = BS_MEM_ALLOC(strlen(temp_pname) + 1);
			memcpy(keys[key_index], temp_pname, strlen(temp_pname) + 1);

			char* temp = json_token_tostr(payload, &tokens[12 + index + 1]);
			char* param_value = BS_MEM_ALLOC(strlen(temp) + 1);
			//memcpy(param_value, temp, strlen(temp) + 1);
            strcpy(param_value, temp);

			printf("%s: %s\r\n", keys[key_index], param_value);
			//x.fieldname = param_name;

			data_t.values[key_index].kind = BSD_STRING;
            data_t.values[key_index].content.string.length = strlen(param_value);
			data_t.values[key_index].content.string.data = param_value;

		}

		data_t.path = name;
		data_t.nbofvalues = max / 2;
		data_t.keys = keys;
    }

    free(tokens);
    if (uid)
    {
    	free(uid);
    }
    if (ts)
    {
    	free(ts);
    }
    free(data);

    return data_t;
}
#if 0
mqtt_data_t json_deserialize_command(jsmntok_t *tokens, char* payload, mqtt_data_t data_t)
{
	char* temp_name = json_token_tostr(payload, &tokens[9]);
	char* name = BS_MEM_ALLOC(strlen(temp_name) + 1);
	memcpy(name, temp_name, strlen(temp_name) + 1);

	//data_t->ticketId = uid;

	int max = (&tokens[11])->size;
	printf("json_deserialize_command - Command: %s (%d params)\r\n", name, max / 2);
	int index = 0;

	char** keys = BS_MEM_ALLOC(max / 2);
	int key_index = 0;
	for(index = 0; index < max; index+=2, key_index++)
	{
		char* temp_pname = json_token_tostr(payload, &tokens[12 + index]);
		keys[key_index] = BS_MEM_ALLOC(strlen(temp_pname) + 1);
        strcpy(keys[key_index], temp_pname);
		//memcpy(keys[key_index], temp_pname, strlen(temp_pname) + 1);

		char* temp = json_token_tostr(payload, &tokens[12 + index + 1]);
		char* param_value = BS_MEM_ALLOC(strlen(temp) + 1);
        strcpy(param_value, temp);
		//memcpy(param_value, temp, strlen(temp) + 1);

		printf("%s: %s\r\n", keys[key_index], param_value);
		//x.fieldname = param_name;

		bsd_data_t x;
#if 0
		if(strcmp(param_value, "true") == 0)
		{
			printf("param bool @ true\r\n");
			x.kind = BSD_BOOL;
			x.content.boolean = true;
		}
		else if(strcmp(param_value, "false") == 0)
		{
			printf("param bool @ false\r\n");
			x.kind = BSD_BOOL;
			x.content.boolean = false;
		}
		else
#endif
		{
            x.kind = BSD_STRING;
			x.content.string.length = strlen(param_value);
			x.content.string.data = param_value;
		}

		data_t.values[key_index] = BS_MEM_ALLOC(sizeof(bsd_data_t));
		memcpy(data_t.values[key_index], &x, sizeof(bsd_data_t));
	}
	data_t.path = name;
	data_t.nbofvalues = max / 2;
	data_t.keys = keys;
	return data_t;
}
#endif

void json_free(mqtt_data_t data_t)
{
    if (data_t.ticketId != NULL)
    {
        free(data_t.ticketId);
    }
    if (data_t.timestamp != NULL)
    {
        free(data_t.timestamp);
    }
    if (data_t.path != NULL)
    {
        free(data_t.path);
    }
    if (data_t.keys != NULL)
    {
        free(data_t.keys);
    }

    if (data_t.values != NULL)
    {
        free(data_t.values);
    }
}
