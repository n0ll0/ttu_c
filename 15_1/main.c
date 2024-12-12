#include <stdio.h>
#include <stdlib.h>

#define ARG_COUNT 2
#define ARG_POS_EXEC 0
#define ARG_POS_FILENAME 1
#define EVEN_OUTPUT_FILE "paaris"
#define ODD_OUTPUT_FILE "paaritu"
int verbose = 0;

void ProcessContentsAndOutput(FILE *fp, FILE *outEven, FILE *outOdd);

int main(int argc, char *argv[])
{
  // Check that argument was provided
  if (argc >= ARG_COUNT) {
    for (int i = 2; i < argc; i++) {
      if (argv[i][0] == '-' && argv[i][1] == 'v') {
        verbose = 1;
        break;
      }
    }
  }
  else
  {
    fprintf(stderr, "Usage %s file.\n", argv[ARG_POS_EXEC]);
    return EXIT_FAILURE;
  }



  // Open the file
  FILE *fp = fopen(argv[ARG_POS_FILENAME], "r");
  if (fp == NULL)
  {
    fprintf(stderr, "Error opening file \"%s\".\n", argv[ARG_POS_FILENAME]);
    return EXIT_FAILURE;
  }
  if (verbose) fprintf(stdout, "Opening file \"%s\"\n", argv[ARG_POS_FILENAME]);

  FILE *paarisFile = fopen(EVEN_OUTPUT_FILE, "w");
  if (paarisFile == NULL) {
    fprintf(stderr, "Error opening file \""EVEN_OUTPUT_FILE"\".\n");
    fclose(fp);
    return EXIT_FAILURE;
  }
  if (verbose) fprintf(stdout, "Opening file \""EVEN_OUTPUT_FILE"\"\n");

  FILE *paarituFile = fopen(ODD_OUTPUT_FILE, "w");
  if (paarituFile == NULL) {
    fprintf(stderr, "Error opening file \""ODD_OUTPUT_FILE"\".\n");
    fclose(fp);
    fclose(paarisFile);
    return EXIT_FAILURE;
  }
  if (verbose) fprintf(stdout, "Opening file \""ODD_OUTPUT_FILE"\"\n");

  ProcessContentsAndOutput(fp, paarisFile, paarituFile);

  // Clean up
  fclose(fp);
  if (verbose) fprintf(stdout, "Closed file \"%s\"\n", argv[ARG_POS_FILENAME]);

  fclose(paarisFile);
  if (verbose) fprintf(stdout, "Closed file \""EVEN_OUTPUT_FILE"\"\n");

  fclose(paarituFile);
  if (verbose) fprintf(stdout, "Closed file \""ODD_OUTPUT_FILE"\"\n");

  return EXIT_SUCCESS;
}

void ProcessContentsAndOutput(FILE *fp, FILE *outEven, FILE *outOdd)
{
  int temp;
  fseek(fp, 0, SEEK_END);
  int *all = calloc(ftell(fp), sizeof(int));
  fseek(fp, 0, 0);
  int i = 0;

  // printf("[i: %d, temp: %d]", i, temp);
  while (fscanf(fp, "%d", &temp) == 1)
  {
    // printf("[i: %d, temp: %d]", i, temp);
    all[i++] = temp;
    if (temp % 2 == 0)
    {
      fprintf(outEven, "%d ", temp);
      if (verbose) fprintf(stdout, "Write \"%d\" to "EVEN_OUTPUT_FILE"\n", temp);
    }
    else
    {
      fprintf(outOdd, "%d ", temp);
      if (verbose) fprintf(stdout, "Write \"%d\" to "ODD_OUTPUT_FILE"\n", temp);
    }
  }
  
  int min = all[i];
  int max = all[i];
  int sum = 0;
  int count = i+1;
  for (;i>=0;--i)
  {
    sum += all[i];
    if (max < all[i]) max = all[i];
    if (min > all[i]) min = all[i];
  }

  fprintf(stdout, "\nmin: %d\nmax: %d\nsum: %d\navg: %f\n", min, max, sum, (float)sum/(float)count);

  fprintf(stdout, "End of file\n");
}
