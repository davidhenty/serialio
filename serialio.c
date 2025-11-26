#include <stdio.h>
#include <stdlib.h>

double wtime(void);
  
int main(int argc, char **argv)
{
  int gig = 1024*1024*1024;
  int n =  gig/2;
  double tstart, tstop;

  if (argc != 2)
    {
      printf("usage: serialio <filename>\n");
      return 1;
    }

  double *x = malloc(n*sizeof(double));

  for (int i = 0; i < n; i++)
    {
      x[i] = (float) i;
    }

  tstart = wtime();
  FILE *fp = fopen(argv[1], "w");
  fwrite(x, sizeof(double), n, fp);
  fflush(fp);
  fclose(fp);
  tstop = wtime();

  printf("Time to write %d bytes was %f seconds (%f GiB/s)\n",
         n, tstop-tstart, (((float) n)*sizeof(double)) / (((float) gig) * (tstop-tstart)));

  return 0;
}

#include <sys/time.h>

/* wall-clock time */

double wtime(void)
{
  struct timeval tp;
  gettimeofday (&tp, NULL);
  return tp.tv_sec + tp.tv_usec/(double)1.0e6;
}
