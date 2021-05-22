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
    char *arg1;
    char *arg2;
    char *arg3;
    char *args[] = {command, arg1, arg2, arg3, NULL};
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
	arg1 = strtok(NULL, " ");
	arg2 = strtok(NULL, " ");
	arg3 = strtok(NULL, " ");
	args[1] = arg1;
	args[2] = arg2;
	args[3] = arg3;
	
	if (!strcmp(command,"exit")){
		return -1;
	}

        else if (!strcmp(arg, "cd")){
		if(chdir(arg1)<0){
			printf("ERROR : Inexistence Directory [%s].\n",arg);
			continue;
		}
		else{
			printf("change directory successfully!\n");
			continue;
		}
	}
	
	else if (!strcmp(arg,"pipe_write")){
		FILE *filep;
		int i;
		filep = popen("ls -l", "w");
		if (filep ==NULL) {
			fprintf(stderr, "popen failed\n");
			exit(1);
		}
		for (i=0; i<30; i++){
			fprintf(filep, "test line\n");
		}
		pclose(filep);
		continue;
	}

	else if (!strcmp(arg,"pipe_read")){
		FILE *file;
		char buf[256];
		file = popen("date", "r"); 
		if(file == NULL) {
			fprintf(stderr, "popen failed\n");
			exit(1);
		}
		if(fgets(buf, sizeof(buf), file) == NULL) {
		fprintf(stderr, "No data from pipe!\n");
		continue;
		}

		printf("line : %s\n", buf);
		pclose(file);
		continue;
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
		    args[0] = "/bin/ls";
	    }

	    else if (!strcmp(arg, "mkdir")){
		    args[0] = "/bin/mkdir";
	    }

	    else if (!strcmp(arg, "rmdir")){
		    args[0] = "/bin/rmdir";
	    }

	    else if (!strcmp(arg, "mv")){
		    args[0] = "/bin/mv";
	    }

	    else if (!strcmp(arg, "rm")){
		    args[0] = "/bin/rm";
	    }

	    else if (!strcmp(arg, "echo")){
		    args[0] = "/bin/echo";
		    char tmp[MAX_LEN_LINE];
		    strncpy(tmp, command + 5, MAX_LEN_LINE - 1);
		    if (tmp[0] == '-'){
			    arg1 = strtok(NULL, " ");
			    args[1] = arg1;
			    strncpy(tmp, command + 8, MAX_LEN_LINE - 1);
			    args[2] = tmp;
		    }
		    else{
			    args[1] = tmp;
			    args[2] = NULL;
		    }
		    args[3] = NULL;
	    }

	    else if (!strcmp(arg, "sleep")){
		    args[0] = "/bin/sleep";
	    }

	    else if (!strcmp(arg, "date")){
		    args[0] = "/bin/date";
	    }
	    
	    else if (!strcmp(arg, "touch")){
		    args[0] = "/bin/touch";
	    }

	    else if (!strcmp(arg, "chmod")){
		    args[0] = "/bin/chmod";
		    printf ("change mode is successfully terminated.\n");
	    }
	    
	    else {
	    	    printf ("ERROR : Inexistence Command [%s].\n",arg);
	    }
	    
	    ret = execve(args[0], args, NULL);
	    if (ret < 0) {
                fprintf(stderr, "execve failed\n");   
                return 1;
            }
	    else{
		exit(0);
	    }
        } 
    }
    return 0;
}



