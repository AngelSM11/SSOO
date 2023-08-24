#include <stdlib.h> // Libreria estandar de C
 #include <stdio.h> // Libreria estandar de C de entrada y salida de informacion
 #include <errno.h> // Para utilizar la variable errno
 #include <unistd.h> // Para utilizar la funcion fork
 #include <sys/wait.h> // Para utilizar la funcion wait
 #include <sys/types.h> // Para utilizar el tipo pid_t

 int main(int argc, char *argv[])
 {
 if(argc<2){
 fprintf(stderr, "Debe pasar el numero de procesos como parametro\n");
 exit(EXIT_FAILURE);
 }

 int nHijos = atoi(argv[1]);
 int status;
 pid_t pid;

 for (int i = 0; i < nHijos; i++){
 switch (fork())
 {
 case -1: // Error
 perror("Fork error\n");
 fprintf(stderr, "errno: %i\n", errno);
 exit(EXIT_FAILURE);
 case 0: // Hijo
 sleep(3);
 break;
 default: // Padre
 pid = wait(&status);
 if(pid>0){
 if(WIFEXITED(status)) printf("Soy el proceso %i. Mi padre es %i y mihijo %i ha salido con estado %i\n", getpid(), getppid(), pid, WEXITSTATUS(status));
 else if(WIFSIGNALED(status)) printf("Soy el proceso %i. Mi padre es %i ymi hijo %i ha salido con señal %i\n", getpid(), getppid(), pid, WTERMSIG(status));
 else if(WIFSTOPPED(status)) printf("Soy el proceso %i. Mi padre es %i ymi hijo %i ha sido parado con señal %i\n", getpid(), getppid(), pid, WSTOPSIG(status));
 exit(WEXITSTATUS(status)+getpid()%10);
 }
 else{
 perror("Wait error\n");
 fprintf(stderr, "errno%i\n", errno);
 exit(EXIT_FAILURE);
 }

 }
 }
 exit(getpid()%10);
 }