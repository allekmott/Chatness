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

int db_connect() {
	printf("Connecting to database...\n");
	struct database *db = db_parse_sconfig();
	printf("Database hostname: %s\n", db->addr);
	free(db);
}

struct database *db_parse_sconfig() {
	printf("Parsing server.conf...\n");
	struct database *db = (struct database *) malloc(sizeof(struct database));
	FILE *sconfig;
	if ((sconfig = fopen("server.conf", "rw")) == 0) {
		printf("No server.conf.\nRun './server --config' to set up database access.\n");
		exit(0);
	}
	// read the sconfig file
	char *line;
	while ((line = read_line(sconfig)) != NULL) {
		char *key = strtok(line, "=");
		char *value = strtok(NULL, "=");
		if (key == NULL || value == NULL)
			continue;

		if (!strcmp(key, "DB_ADDR")) {
			printf("\tFound DB_ADDR\n");
			db->addr = value;
		} else if (!strcmp(key, "DB_USER")) {
			printf("\tFound DB_USER\n");
			db->user = value;
		} else if (!strcmp(key, "DB_PASS")) {
			printf("\tFound DB_PASS\n");
			db->pass = value;
		}
		free(line);
	}
	return db;
}


int db_user_exists(char *username) {
	// query database and such
	return 0;
}