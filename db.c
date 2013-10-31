/**
 * db.c
 * @creation 29.10.2013
 * @author Allek
 **/

#include <stdio.h>
#include <stdlib.h>

#include "chat.h"

void dbconfig() {
	FILE *sconfig;
	if ((sconfig == fopen("server.conf", "rw")) == NULL) {
		// here
		printf("No server.conf.")
	}
}


int user_exists(char *username) {

}