#include 




int main()
{
    int n, status;
    pid_t childpid;

    printf("Hijos que quiera crear: \n");
    scanf("%d", &n);

    printf("Soy el padre con ID %d \n", getpid());

    for (int i=0; i<n; i++){
        
        switch (fork()){
        
        case -1:
            printf("Error en la creación del proceso hijo \n");
            exit(EXIT_FAILURE);
        
        case 0:
            printf("Soy el hijo numero %d con ID %d del proceso %d \n", i+1, getpid(), getppid());
            exit(EXIT_SUCCESS);

        default:
            printf("Esperando a que mi hijo %d termine \n", i+1);
        }
    }

    //mandar hijos del mismo



} 