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

struct database *db_connnect() {
	struct database *db = (struct database *) malloc(sizeof(struct database));
	FILE *sconfig;
	if ((sconfig == fopen("server.conf", "rw")) == 0) {
		// here
		printf("No server.conf.");
	}
	return db;
}

void db_read_sconfig(FILE *sconfig) {
	// read the sconfig file

}


int db_user_exists(char *username) {
	// query database and such
	return 0;
}