/**
 * server.c
 * @creation 21.7.2013
 * @author Allek
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include <unistd.h>

#include "server.h"
#include "chat.h"


int socket_fd;
char *msg_buf;
static struct user *all_users;
struct user *logged_in;
FILE *chatdat;


int main(int argc, char *argv[]) {
	handle_args(argc, argv);
	open_chatdat();
	print_version();
	init_net();
	serve();
}

void handle_args(int argc, char *argv[]) {
	// TODO that arg lib thing...
	char opt_c;
	while ((opt_c = getopt(argc, argv, "a")) != EOF)
		switch (opt_c) {
			case 'a': chatdat_gen(); exit(0);
		}

	argc -= optind;
	argv += optind;
	return;
}

void process_con(int socket_fd, struct sockaddr_in *client_addr) {
	char client_info_str[50];
	char client_addr_str[40];

	sprintf(client_addr_str, "%s:%i", inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
	sprintf(client_info_str, "Received connection from %s", client_addr_str);

	slog(client_info_str);

	char hello_str[40];
	sprintf(hello_str, "Saying hello to %s.", client_addr_str);

	slog(hello_str);
	send_msg(socket_fd, "[Server] Hello, and welcome to Chatness.\n");

	prompt_user_login(socket_fd, client_addr);

	msg_buf = (char *) malloc(1000);

	if (msg_buf == NULL)
		error("Cannot allocate buffer memory");
	
	while (1) {
		flush(msg_buf);

		if (get_line(socket_fd, msg_buf) == 0) {
			char null_msg_str[70];
			sprintf(null_msg_str,
				"NULL/-1 return on read from %s; Assuming disconnection. Exiting.", client_addr_str);
			slog(null_msg_str);
			exit(0);
		}
		
		if (strlen(msg_buf) == 0)
			continue;

		//slog(msg_buf);

		// construct client_msg struct
		struct client_msg msg_s;
		msg_s.socket_fd = socket_fd;
		msg_s.client_addr = client_addr;
		msg_s.msg = msg_buf;
		msg_s.len = 1000;

		process_msg(&msg_s);
	}

	cleanleave(); // DAJSLKJFSOSAJDOI
}

void process_msg(struct client_msg *msg_s) {
	char proc_msg_str[msg_s->len + 40];
	char addr_str[20];
	
	struct sockaddr_in *client_addr = msg_s->client_addr;

	sprintf(addr_str, "%s:%i",
		inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
	sprintf(proc_msg_str, "[%s]: %s", addr_str, msg_s->msg);
	slog(proc_msg_str);

	send_msg(msg_s->socket_fd, "LOLOLOL\n");
}

void slog(char *msg) {
	printf("%s\n", msg);
}

void flush(char *buf) {
	//slog("Flushing buffer");
	*buf = *buf | *buf;
}

void sighandle(int signal) {
	slog("\nSignal received, freeing buffer memory.");
	cleanleave();
}

void cleanleave() {
	slog("Lulz, gotta go. kbye\n");
	
	if (msg_buf != 0)
		free(msg_buf);
	if (all_users != 0)
		free_user_chain(all_users);

	shutdown(socket_fd, SHUT_RDWR);

	exit(0);
}

void prompt_user_login(int socket_fd, struct sockaddr_in *client_addr) { //TODO this 
	prompt:	
	send_msg(socket_fd, "Please enter your username:\n");
	char uname[50]; // <- Fix vulnerability
	get_line(socket_fd, uname);

	if (user_exists(uname, all_users))
		send_msg(socket_fd, "Password:\n");
	else {
		char no_user[100];
		sprintf(no_user, "The user '%s' does not exist.\n", uname);
		send_msg(socket_fd, no_user);
		goto prompt;
	}
}

void send_help(int socket_fd) {
	send_msg(socket_fd, "lol?");
}

void print_version() {
	char version_str[30];
	sprintf(version_str, "Chatness Server v%s", S_VERSION);
	slog(version_str);
}

void open_chatdat() {
	slog("Opening chat.dat");
	chatdat = fopen("chat.dat", "rw");
	if (chatdat == NULL)
		error("trying to open chat.dat");
	all_users = chatdat_parse_users(chatdat);
}

void init_net() {
	struct sockaddr_in host_addr; // server address struct
	int yes = 1;

	slog("Begin network initialization...");

	slog("Opening socket");
	if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) // open stream socket, ip
		error("opening socket");

	slog("Making address reusable");
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) // reuse address
		error("setting socket option SO_REUSEADDR");

	// host address stuct
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(PORT);
	host_addr.sin_addr.s_addr = 0;
	memset(&host_addr.sin_zero, '\0', 8); // zero out rest of struct

	char port_str[20];
	sprintf(port_str, "Binding to port %i", PORT);
	slog(port_str);

	if (bind(socket_fd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1) // bind to port 1337
		error("binding to socket");

	slog("Attempting to listen");
	if (listen(socket_fd, 5) == -1) // attempt to listen
		error("listening on socket");	
}

void serve() {
	int new_socket_fd; // socket descriptor for new connection
	struct sockaddr_in client_addr; // client address struct
	socklen_t sin_size; // size of address struct
	sin_size = sizeof(struct sockaddr_in);

	slog("Initialization complete, accepting connections!");
	while (1) {
		new_socket_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &sin_size); // accept connection
		int me = fork();
		if (me == 0) {
			signal(SIGINT, sighandle);
			signal(SIGTERM, sighandle);
			process_con(new_socket_fd, &client_addr);
		}
	}
}