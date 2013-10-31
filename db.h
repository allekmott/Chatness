/**
 * db.h
 * @creation 29.10.2013
 * @author Allek
 **/
 
#include "chat.h"
#include <stdio.h>

#ifndef DB_H
#define DB_H

/**
 * Read server config and connect to database.
 * @since 0.0.2.3
 **/
void db_config();

/**
 * Read server.conf if it exists.
 * @since 0.0.2.4
 **/
void db_read_sconfig(FILE *sconfig);

 /**
  * Check whether or not a user exists.
  * @since 0.0.2.3
  **/
int db_user_exists(char *username);


#endif