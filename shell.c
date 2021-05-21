#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

#define MAX_LEN_LINE    100
#define LEN_HOSTNAME    30
#define LEN_DIR    100

int main(void)
{
    char command[MAX_LEN_LINE];
    char *arg;
    char *arg2;
    char *args[] = {command, arg, arg2, NULL};
    int ret, status;
    pid_t pid, cpid;

    char hostname[LEN_HOSTNAME + 1];
    memset(hostname, 0x00, sizeof(hostname));
    gethostname(hostname, LEN_HOSTNAME);

    while (true) {
        char *s;
        int len;
	char pwd[LEN_DIR + 1];
	getcwd(pwd,sizeof(pwd));

	printf("\033[32m%s\033[32m@%s:\033[34m%s\033[0m$ ", getpwuid(getuid())->pw_name, hostname,pwd);
       
	s = fgets(command, MAX_LEN_LINE, stdin);
	
	if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }
    	
	len = strlen(command);
	printf("%d\n", len);	
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0'; 
        }
	
	arg = strtok(command," ");

	if (!strcmp(command,"exit")){
		return -1;
	}

        else if (!strcmp(arg, "cd")){
		arg = strtok(NULL, " ");
		if(chdir(arg)<0){
			printf("ERROR : Inexistence Directory [%s].\n",arg);
			continue;
		}
		else{
			printf("change directory successfully!\n");
			continue;
		}
	}

        printf("[%s]\n", command);
     
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } 
        if (pid != 0) {  /* parent */
            cpid = waitpid(pid, &status, 0);
            if (cpid != pid) {
                fprintf(stderr, "waitpid failed\n");        
            }
            printf("Child process terminated\n");
            if (WIFEXITED(status)) {
                printf("Exit status is %d\n", WEXITSTATUS(status)); 
            }
        }
        else {  /* child */
	    if (!strcmp(arg, "ls")){
		    arg = strtok(NULL, " ");
		    args[0] = "/bin/ls";
		    args[1] = arg;
		    args[2] = NULL;
	    }

	    else if (!strcmp(arg, "mkdir")){
		    arg = strtok(NULL, " ");
		    args[0] = "/bin/mkdir";
		    args[1] = arg;
		    arg2 = strtok(NULL, " ");
		    args[2] = arg2;
	    }

	    else if (!strcmp(arg, "rmdir")){
		    arg = strtok(NULL, " ");
		    args[0] = "/bin/rmdir";
		    args[1] = arg;
		    arg2 = strtok(NULL, " ");
		    args[2] = arg2;
	    }
     
	    else {
	    	    printf ("ERROR : Inexistence Command [%s].\n",arg);
	    }
	    ret = execve(args[0], args, NULL);
	    if (ret < 0) {
                fprintf(stderr, "execve failed\n");   
                return 1;
            }
	    
        } 
    }
    return 0;
}


