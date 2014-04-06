#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

struct command {
	char *process;
	char *args;
	char *path;
};

#define PROCESS_MAX_NAME_SIZE 3
#define ARGS_MAX_SIZE 128
#define PATH_MAX_SIZE 128
#define FD_STDIN 0 
#define FD_STDOUT 1
#define FD_STDERR 2

void usr1_sig_handler(int sig) {
}

void shell(int fd_input, int fd_output, struct command* current) {
	if(strcmp(current->args, "COMMAND_TOO_LONG")==0) {
		char* buf = "Command too long!\n";
		write(fd_output, buf, strlen(buf)); 
	}
	
	char* buf = "azsh:$ ";
	write(fd_output, buf, strlen(buf));
}

void process(int fd_input, int fd_output, struct command* current) {
	char* buf = malloc(32*sizeof(char));
	if(strcmp(current->process, "moo")==0) {
		buf = "COWMOOO!\n";
		write(fd_output, buf, strlen(buf));
	} else if(strcmp(current->process, "exit")==0) { 
		exit(EXIT_SUCCESS);
	} else if(strcmp(current->process, "azsh")!=0) {
		int pid, stat_loc;

		pid = fork();
		if (pid == 0) {
			execl(current->process, ".", NULL);

			execlp(current->process, ".", NULL);

			kill(getppid (), SIGUSR1); // signal invalid command to parent

			buf = "Invalid command!\n";
			write(fd_output, buf, strlen(buf));

			exit(EXIT_SUCCESS);
		} else {
			do {
	            int w = waitpid(pid, &stat_loc, WUNTRACED);
	            if (w == -1) {
	                //error happened
	            }

	           if (WIFEXITED(stat_loc) && WEXITSTATUS(stat_loc) != 0) {
	           		sprintf(buf,"Child exited with status %d\n", WEXITSTATUS(stat_loc));
					write(fd_output, buf, strlen(buf));
	            } else if (WIFSIGNALED(stat_loc)) {
	            	sprintf(buf,"Child killed by signal %d\n", WTERMSIG(stat_loc));
					write(fd_output, buf, strlen(buf));
	            } else if (WIFSTOPPED(stat_loc)) {
	            	sprintf(buf,"Child stopped by signal %d\n", WSTOPSIG(stat_loc));
					write(fd_output, buf, strlen(buf));
	            } 
        	} while (!WIFEXITED(stat_loc) && !WIFSIGNALED(stat_loc));
		}
	}

	shell(fd_input, fd_output, current);
}

void clean_process_struct(struct command* current) {
	strcpy(current->process, "azsh");
	strcpy(current->args, "");
	strcpy(current->path, "");
}

void wait_and_process_input(int fd_input, struct command* current) {
	clean_process_struct(current);

	char* input_buffer = malloc(PROCESS_MAX_NAME_SIZE+ARGS_MAX_SIZE+3);
	int sz = read(fd_input, input_buffer, PROCESS_MAX_NAME_SIZE+ARGS_MAX_SIZE+3);

	if(strlen(input_buffer) == PROCESS_MAX_NAME_SIZE+ARGS_MAX_SIZE+3) {
		//command too long
		strcpy(current->process, "azsh");
		strcpy(current->args, "COMMAND_TOO_LONG");
	} else {
		input_buffer[sz-1]='\0'; //replace \n with \0
		//@TODO check if valid
		strcpy(current->process, input_buffer);
	}

	//@TODO ARGUMENTS
}

int main(int argc, char **argv) {
	int fd_input = FD_STDIN;
	int fd_output = FD_STDOUT; 

	struct sigaction usr_action;
	sigset_t block_mask;

	/* Establish the signal handler. */
	sigfillset (&block_mask);
	usr_action.sa_handler = usr1_sig_handler;
	usr_action.sa_mask = block_mask;
	usr_action.sa_flags = 0;
	sigaction(SIGUSR1, &usr_action, NULL);

	//@TODO file input/output instead of standard

	struct command current;
	current.process = malloc(PROCESS_MAX_NAME_SIZE);
	current.args = malloc(ARGS_MAX_SIZE);
	current.path = malloc(PATH_MAX_SIZE);

	clean_process_struct(&current);

	while(1) {
		process(fd_input,fd_output,&current);
		wait_and_process_input(fd_input, &current);
	}

	exit(EXIT_SUCCESS);
	return 0;
}