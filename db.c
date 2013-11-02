/**
 * db.c
 * @creation 29.10.2013
 * @author Allek
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chat.h"
#include "db.h"

int db_connect(struct database_conf *db) {
	printf("Connecting to database...\n");
	printf("Database hostname: %s\n", db->addr);
	free(db);
}


int db_user_exists(char *username) {
	// query database and such
	return 0;
}