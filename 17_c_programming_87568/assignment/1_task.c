#include <stdio.h>
#include <string.h>
void foo(char *s) {
char buf[4];
strcpy(buf, s);
printf("You entered: %s", buf);
}
void bar() {
printf("\n\nWhat? I was not supposed to be called!\n\n");
fflush(stdout);
}
int main(int argc, char *argv[]) {
if (argc != 2) {
printf("Usage: %s some_string", argv[0]);
return 2;
}
foo(argv[1]);
return 0;
}
