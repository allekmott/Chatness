/**
 * chat.h
 * @creation 21.7.2013
 * @author Allek
**/

#ifndef CHAT_H
#define CHAT_H

/**
 * Print error message and exit.
 * @since 0.0.1
**/
void error(char *err_msg); // 0.0.1

/**
 * Send message with provided socket file descriptor.
 * @since 0.0.1
**/
int send_msg(int sockfd, char *buffer); // 0.0.1

/**
 * Receive a message from the provided socket file descriptor.
 * @since 0.0.1
**/
int get_line(int sockfd, char *dest_buffer); // 0.0.1

/**
 * Receive a message from the provided socket file descriptor,
 * and limit to the provided buffer size. Message will be trimmed if
 * it exceeds the buffer size.
 * @since 0.0.2
**/
int sget_line(int sockfd, char *dest_buffer);

/**
 * Data structure for user
 * @since 0.0.2
**/
struct user {
	const char *username;
	const char *password;
	struct user *next;
};

// LOGIN ERROR CODES
#define LOGIN_GOOD 0
#define LOGIN_DNE 1
#define LOGIN_PASS_BAD 2

/**
 * Attempt to log a user in;
 * Compares provided username and password to those found in
 * the user list provided.
 * Returns 0 on success, error code on failure.
 * @since 0.0.2
**/
int login(const char *username, const char *password, struct user *list_start);

/**
 * Returns whether or not the provided username has a corresponding user
 * in the linked list of users provided.
 * @since 0.0.2
**/
int user_exists(const char *username, struct user *list_start);

/**
 * Return visual feedback of a login error code.
 * @since 0.0.2
**/
char *login_err_txt(int err_code);

/**
 * Constructs linked list of users from information in chat.dat file.
 * Returns first user in list on success, or NULL on error.
 * @note [WARNING] Allocates memory on heap. Corresponding
 * @since 0.0.2
**/
struct user *chatdat_parse_users(FILE *chatdat);

#define USER_BUFFER_SIZE 20

// CHATDAT LINE TYPES
#define CHATDAT_UNKNOWN -1
#define CHATDAT_BLANK 0
#define CHATDAT_COMMENT 1
#define CHATDAT_USER 2
#define CHATDAT_ROOM 3

/**
 * Returns string value of chat.dat line type value.
 * @since 0.0.2
**/
char *chatdat_type_string(int type);

/**
 * Obtain the type of a provided line. Basically, cycles through characters
 * until a nonbreaking whitespace is found, and checks to see if it is
 * $, @, or #.
 * @since 0.0.2
**/
int chatdat_line_type(const char *line);

/**
 * Returns a pointer to the first token in a chat.dat line.
 * @since 0.0.2
**/
char *chatdat_get_token(const char *line);

/**
 * Purge a line of whitespace.
 * @since 0.0.2
**/
char *chatdat_clean_line(const char *line);

/**
 * Parses a user struct out of a line from a chat.dat file.
 * @since 0.0.2
**/
struct user *chatdat_parse_uline(const char *line);

/**
 * Checks to see if any tokens or weird characters are included in the
 * provided string.
 * If so, returns false, otherwise, returns 1.
**/
int chatdat_valid_string(const char *string);

/**
 * Obtains the user with the provided user name from the list of users
 * provided.
 * Returns NULL if user is not present.
 * @since 0.0.2
**/
struct user *get_user(const char *username, struct user *list_start);

/**
 * Prints user information.
 * @since 0.0.2
**/
void print_user_info(struct user *u);

/**
 * Prints user info for every user found in a linked list.
 * @since 0.0.2
**/
void chain_user_info(struct user *start);

/**
 * Free a chain of user structs.
 * @since 0.0.2
**/
void free_user_chain(struct user *start);

/**
 * Read a line from the provided FILE pointer.
 * @since 0.0.2
**/
char *read_line(FILE *file);

#define LINE_BUFFER_SIZE 128

/**
 * Prompt server admin for additions/modifications to chat.dat.
 * @since 0.0.3.1
 **/
void chatdat_gen();

/**
 * Add a user to chat.dat.
 * @since 0.0.3.2
 **/
void chatdat_gen_add_user(struct user *chatdat_users);

#endif
