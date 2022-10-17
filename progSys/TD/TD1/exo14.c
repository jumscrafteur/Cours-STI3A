#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <stdio.h>

int main()
{
  struct passwd *pwd = getpwnam("jumscrafteur");

  printf("%s", pwd->pw_name);
}