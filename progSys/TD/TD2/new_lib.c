#include "new_lib.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/errno.h>

int ind = -1;
char buffer;

void *new_malloc(int size)
{
	void *allocation = sbrk(size);
 	if ( allocation == (void*)-1){
		perror("Erreur %s survenue \n");
    		return NULL;
	}
	return allocation;
}


void new_printf(char *msg){
	if (ind == -1){
		buffer = new_malloc(BUF_SIZE);
		if(buffer == NULL){
			perror("Error");
		}
	}
	ind = 0;

	
	for (i=0;msg[i]!='\n';i++){
		if (msg[i] == '\n' || ind == BUF_SIZE){
			if(write(1,buffer,ind)==-1){
				perror("Error");
			}
			ind = 0;
		} 
	       	if(msg[i] != '\n'){
			buffer[ind] = msg[i];
			ind ++;
		}
	}
}

void new_exit(){
	_exit()
}
