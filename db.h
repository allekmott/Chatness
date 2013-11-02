/**
 * db.h
 * @creation 29.10.2013
 * @author Allek
 **/
 
#include "chat.h"
#include <stdio.h>

#ifndef DB_H
#define DB_H

struct database_conf {
	const char *host;
	const char *user;
	const char *pass;
};

/**
 * Connect to database.
 * @since 0.0.2.3
 **/
int db_connect(struct database_conf *db);

/**
 * Check whether or not a user exists.
 * @since 0.0.2.3
 **/
int db_user_exists(char *username);


#endif