#include <stdio.h>
#include <unistd.h>

int main(){
	#ifdef _POSIX_SOURCE
	printf("_POSIX_SOURCE=%d\n",_POSIX_SOURCE);
	#endif

	#ifdef _POSIX_C_SOURCE
	printf(" _POSIX_C_SOURCE=%ld\n", _POSIX_C_SOURCE);
	#endif

	#ifdef  _XOPEN_SOURCE
	printf(" _XOPEN_SOURCE=%d\n", _XOPEN_SOURCE);
	#endif

	#ifdef  _XOPEN_SOURCE_EXTENDED
	printf(" _XOPEN_SOURCE_EXTENDED=%d\n", _XOPEN_SOURCE_EXTENDED);
	#endif


	printf("ARG_MAX = %li\n",sysconf(_SC_ARG_MAX));
	printf("VERSION = %li\n", sysconf(_SC_VERSION));

	return 0;
}
