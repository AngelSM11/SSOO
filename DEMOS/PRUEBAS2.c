#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


int main(int argc, char *argv[]){

pid_t child_pid, wpid;
int status;
FILE *fp;
char c;

for(int i=0;i<atoi(argv[1]);i++){

switch(child_pid = fork()){


case -1:
{      /* fork() failed */
    perror("fork");
    exit(EXIT_FAILURE);
}


case 0:
{       /* This is the child */
    /* Child does some work and then terminates */
    printf("Hijo %d\n", getpid());
    if(i==0){
        fp = fopen("estudiar.txt", "r");

        while(fscanf(fp, "%s", &c)>0){
            printf("%s\n", &c);
        }
        fclose(fp);        
    }
    if(i==1){
        if(execlp(argv[2], argv[2], (char*) NULL)<0){
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }
    
    exit(EXIT_SUCCESS);
    

}
default:
    printf("Padre %d generando hijo\n", getpid());
}
}
    wpid = waitpid(child_pid, &status, WUNTRACED);                  /* This is the parent */
    do {
        
        if (wpid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }


        if (WIFEXITED(status)) {
            printf("Hijo %d terminado padre %d con status=%d\n",wpid, getpid(),  WEXITSTATUS(status));


        } else if (WIFSIGNALED(status)) {
            printf("child killed (signal %d)\n", WTERMSIG(status));


        } else if (WIFSTOPPED(status)) {
            printf("child stopped (signal %d)\n", WSTOPSIG(status));



        } else {    /* Non-standard case -- may never happen */
            printf("Unexpected status (0x%x)\n", status);
        }
    } while ((wpid=wait(&status))!=0);
}


