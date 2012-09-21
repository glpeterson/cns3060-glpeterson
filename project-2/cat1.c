#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  int useStdin = 0;
  int useLineNum = 0;
  int argCounter = 1;
  int lineNum = 1;
  long fSize = 0;
  char inChar;
  char lineBuff[5] = "     ";
  FILE *oFile;

  if (argc < 2)
  {
    useStdin = 1;
  }
  else
  {
    if (argv[1][0] == '-')
    {
      if (argv[1][1] == 'n')
      {
        useLineNum = 1;
        argCounter = 2;
      }
      else
      {
        perror("Invalid option, use '-n'");
        return(0);
      }

      if (argc < 3)
      {
        useStdin = 1;
      }
    }
  }

  if (useStdin)
  {
    inChar = fgetc(stdin);

    if (useLineNum)
    {
      sprintf (lineBuff, "%i-", lineNum);
      fwrite (lineBuff, sizeof(char), sizeof(lineBuff), stdout);
      lineNum = lineNum + 1;
    }

    while (!feof(stdin) && !ferror(stdin))
    {
      fputc (inChar, stdout);

      if (inChar == '\n' && useLineNum)
      {
        inChar = fgetc(stdin);
        sprintf (lineBuff, "%i-", lineNum);
        fwrite (lineBuff, sizeof(char), sizeof(lineBuff), stdout);
        lineNum = lineNum + 1;
      }
      else
      {
        inChar = fgetc(stdin);
      }
    }

    if (ferror(stdin))
    {
      perror("Error while reading from stdin");
      clearerr(stdin);
    }
  }
  else
  {
    while(argCounter < argc)
    {
      oFile = fopen (argv[argCounter],"r");
      argCounter = argCounter + 1;

      if (oFile != NULL)
      {
        fseek (oFile , 0 , SEEK_END);
        fSize = ftell (oFile);
        rewind (oFile);

        inChar = getc(oFile);

        if (ferror(oFile))
        {
          perror("File read error.");
          return(0);
        }

        if (useLineNum)
        {
          printf ("\n%i - ", lineNum);
          lineNum = lineNum + 1;
        }

        while (inChar != EOF)
        {
           putchar(inChar);

           if (inChar == '\n' && useLineNum)
           {
             printf("%i - ", lineNum);
             lineNum = lineNum + 1;
           }

           inChar = getc(oFile);
        }

        fclose (oFile);
      }
      else
      {
        perror("Unable to open one of the files.");
        return(0);
      }
    }
  }
  
  return 0;
}
