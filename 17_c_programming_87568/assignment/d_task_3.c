#include <stdio.h>
#include <getopt.h>
int main ( int argc, char **argv) {
 int option_index = 0;
 while (( option_index = getopt(argc, argv, "a:z")) != -1){
   switch (option_index) {
     case 'c':
      printf("First field: %c\n", option_index);
       break;
     case 'd':
       printf("Group is selected: %c\n", option_index);
       break;
     case 'u':
      printf("U option is selected %c\n", option_index);
     default:
      printf("Option incorrect\n");
      return 1;
     } //end block for switch
   }  //end block for while
 return 0;
} // end main block
