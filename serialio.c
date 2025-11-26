#include <stdio.h>
#include <stdlib.h>

double wtime(void);
  
int main(void)
{
  int gig = 1024*1024*1024;
  int n =  gig/2;
  double tstart, tstop;

  double *x = malloc(n*sizeof(double));

  for (int i = 0; i < n; i++)
    {
      x[i] = (float) i;
    }

  tstart = wtime();
  FILE *fp = fopen("data.out", "w");
  fwrite(x, sizeof(double), n, fp);
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
