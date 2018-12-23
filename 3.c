#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
printf("UID: %d EUID: %d\n",getuid(),geteuid());
FILE* fl = fopen("/home/user/Sources/Unix/user_file/example","r");
if(fl==NULL){
perror("Error");
return EXIT_FAILURE;
}
fclose(fl);
return EXIT_SUCCESS;
}
