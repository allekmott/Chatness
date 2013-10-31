/**
 * db.h
 * @creation 29.10.2013
 * @author Allek
 **/
 
#include "chat.h"

/**
 * Read server config and connect to database.
 * @since 0.0.2.3
 **/
void dbconfig();

 /**
  * Check whether or not a user exists.
  * @since 0.0.2.3
  **/
int user_exists(char *username);

