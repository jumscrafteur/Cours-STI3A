#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    pid_t status;
    int fd = open("fichier.txt", O_RDWR | O_CREAT, 0644);
    char buffer[4];

    printf("[%d] Je vais engendrer\n", getpid());
    status = fork();
    switch (status)
    {
    case -1:
        perror("Creation processus");
        exit(EXIT_FAILURE);
    case 0:
        printf("[%d] Je viens de naitre\n", getpid());
        printf("[%d] Mon père est %d\n", getpid(), getppid());

        lseek(fd, 3, SEEK_SET);
        write(fd, "foo", 3);

        sleep(2);

        lseek(fd, 3, SEEK_SET);
        read(fd, buffer, 3);
        buffer[3] = '\0';

        printf("[%d] Les 3 caractères lus à l'offset 3 sont : %s\n", getpid(), buffer);

        // Ferme le fichier
        close(fd);

        break;

    default:
        printf("[%d] J'ai engendre\n", getpid());
        printf("[%d] Mon fils est %d\n", getpid(), status);

        lseek(fd, 3, SEEK_SET);
        write(fd, "bar", 3);

        sleep(1);

        lseek(fd, 3, SEEK_SET);
        read(fd, buffer, 3);
        buffer[3] = '\0';

        printf("[%d] Les 3 caractères lus à l'offset 3 sont : %s\n", getpid(), buffer);

        // Ferme le fichier
        close(fd);

        break;
    }

    printf("[%d] Je termine \n", getpid());
    exit(EXIT_SUCCESS);
}
