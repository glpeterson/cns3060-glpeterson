#include <stdio.h>

int main(int argc, char *argv[])
{
   int i = 1;

   printf("Gary Peterson\nCNS 3060\n\n");

   while(i < argc)
   {
      printf("%s\n", argv[i]);
      i++;
   }
   
   return 0;
}
