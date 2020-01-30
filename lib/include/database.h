#pragma once

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

/*
 *	query language:
 *	
 *				ADD [SECTION]
 *				ADD [KEY] FROM [SECTION]
 *				GET [KEY] FROM [SECTION]
 *				SET [KEY] FROM [SECTION] AS [VALUE]
 * */

#define DBMSG_SUCC "OPERATION SUCCEDED"
#define DBMSG_FAIL "OPERATION FAILED"
#define DBMSG_ERR "DATABASE FAILURE"

typedef struct {
    FILE* dbstrm;	//stream to the database
    pthread_rwlock_t* lock;
    char* dbcache;	//database buffer cache
    uint8_t dbit;	//dirty bit
} database_t;

/*	Initiazlize database from file return 1 and set properly errno on error	*/
extern int database_init(database_t* database, const char *filename);
/*	Close database return EOF and set properly errno on error */
extern int database_close(database_t* database);
/*	Execute a query return 1 and set properly errno on error */
extern int database_execute(database_t* database, const char *query, char **result);
