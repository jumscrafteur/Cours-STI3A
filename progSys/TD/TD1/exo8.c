#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

int main(){
		  //(void)syscall(SYS_write,STDOUT_FILENO, "hello\n",6);
		  int ret = syscall(SYS_write,3, "hello\n",6);
		  if (ret == -1){
					 perror("Erreur");
					 return 1;
		  }
}
