#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
pid_t child_pid, wpid;
pid_t childd;

int status;


switch(child_pid = fork()){
case -1:     /* fork() failed */
    perror("fork");
    exit(EXIT_FAILURE);



case 0:       /* This is the child */
    /* Child does some work and then terminates */
    printf("Hijo %d generando con padre %d mis %s hijos\n", getpid(), getppid(), argv[1]);
    
    for(int i=0; i<atoi(argv[1]);i++){
        //printf("%d\n",i);
        switch(childd = fork()){
        case -1:     /* fork() failed */
            perror("fork");
            exit(EXIT_FAILURE);

        case 0:       /* This is the child */
    /* Child does some work and then terminates */
            printf("NIETO %d generado mi padre es %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
            
        default:
            //printf("Padre %d generando hijo %d\n", getpid(), childd_pid);
            printf(" ");
            do {
        wpid = waitpid(childd, &status, WUNTRACED);
        if (wpid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }


        if (WIFEXITED(status)) {
            printf("Padre %d,ha finalizado el hijo %d con el estado %d\n",getpid(), wpid, WEXITSTATUS(status));


        } else if (WIFSIGNALED(status)) {
            printf("child killed (signal %d)\n", WTERMSIG(status));


        } else if (WIFSTOPPED(status)) {
            printf("child stopped (signal %d)\n", WSTOPSIG(status));


        } else {    /* Non-standard case -- may never happen */
            printf("Unexpected status (0x%x)\n", status);
        }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            
    
    
        }

    }

   

    exit(EXIT_SUCCESS);


    default:
    printf("Padre %d generando hijo %d\n", getpid(), child_pid);
}


                    /* This is the parent */
    do {
        wpid = waitpid(child_pid, &status, WUNTRACED);
        if (wpid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }


        if (WIFEXITED(status)) {
            printf("Padre %d,ha finalizado el hijo %d con el estado %d\n",getpid(), wpid, WEXITSTATUS(status));


        } else if (WIFSIGNALED(status)) {
            printf("child killed (signal %d)\n", WTERMSIG(status));


        } else if (WIFSTOPPED(status)) {
            printf("child stopped (signal %d)\n", WSTOPSIG(status));

        } else {    /* Non-standard case -- may never happen */
            printf("Unexpected status (0x%x)\n", status);
        }
    } while ((wait(&status)!=0));
    

}