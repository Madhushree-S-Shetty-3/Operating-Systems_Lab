#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void
sort (int proc[], int b[], int pt[], int n)
{
  int temp = 0;
  for (int i = 0; i < n; i++)
	{
	  for (int j = i; j < n; j++)
		{
		  if (pt[j] < pt[i])
			{
			  temp = pt[i];
			  pt[i] = pt[j];
			  pt[j] = temp;
			  temp = b[j];
			  b[j] = b[i];
			  b[i] = temp;
			  temp = proc[i];
			  proc[i] = proc[j];
			  proc[j] = temp;
			}
		}
	}
}

int
gcd (int a, int b)
{
  int r;
  while (b > 0)
	{
	  r = a % b;
	  a = b;
	  b = r;
	}
  return a;
}

int
lcmul (int p[], int n)
{
  int lcm = p[0];
  for (int i = 1; i < n; i++)
	{
	  lcm = (lcm * p[i]) / gcd (lcm, p[i]);
	}
  return lcm;
}


void
main ()
{
  int n;
  printf ("Enter the number of processes:");
  scanf ("%d", &n);
  int proc[n], b[n], pt[n], rem[n];
  printf ("Enter the CPU burst times:\n");
  for (int i = 0; i < n; i++)
	{
	  scanf ("%d", &b[i]);
	  rem[i] = b[i];
	}
  printf ("Enter the time periods:\n");
  for (int i = 0; i < n; i++)
	scanf ("%d", &pt[i]);
  for (int i = 0; i < n; i++)
	proc[i] = i + 1;

  sort (proc, b, pt, n);
  //LCM
  int l = lcmul (pt, n);
  printf ("LCM=%d\n", l);

  printf ("\nRate Monotone Scheduling:\n");
  printf ("PID\t Burst\tPeriod\n");
  for (int i = 0; i < n; i++)
	printf ("%d\t\t%d\t\t%d\n", proc[i], b[i], pt[i]);

  //feasibility
  double sum = 0.0;
  for (int i = 0; i < n; i++)
	{
	  sum += (double) b[i] / pt[i];
	}
  double rhs = n * (pow (2.0, (1.0 / n)) - 1.0);
  printf ("\n%lf <= %lf =>%s\n", sum, rhs, (sum <= rhs) ? "true" : "false");
  if (sum > rhs)
	exit (0);

  printf ("Scheduling occurs for %d ms\n\n", l);

  //RMS 
  int time = 0, prev = 0, x = 0;
  while (time < l)
	{
	  int f = 0;
	  for (int i = 0; i < n; i++)
		{
		  if (time % pt[i] == 0)
			rem[i] = b[i];
		  if (rem[i] > 0)
			{
			  if (prev != proc[i])
				{
				  printf ("%dms onwards: Process %d running\n", time,
						  proc[i]);
				  prev = proc[i];
				}
			  rem[i]--;
			  f = 1;
			  break;
			  x = 0;
			}
		}
	  if (!f)
		{
		  if (x != 1)
			{
			  printf ("%dms onwards: CPU is idle\n", time);
			  x = 1;
			}
		}
	  time++;
	}
}
