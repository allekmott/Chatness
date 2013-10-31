/**
 * db.c
 * @creation 29.10.2013
 * @author Allek
 **/

#include <stdio.h>
#include <stdlib.h>

#include "chat.h"

void db_config() {
	FILE *sconfig;
	if ((sconfig == fopen("server.conf", "rw")) == NULL) {
		// here
		printf("No server.conf.");
	}
}

void db_read_sconfig(FILE *sconfig) {

}


int db_user_exists(char *username) {

}