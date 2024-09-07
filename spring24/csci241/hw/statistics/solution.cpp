#include <iostream>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;


int minimum(int array[], int n)
{
 int min = array[0];

 for (int i = 1; i < n; i++)
 {
  if (array[i] < min)
    min = array[i];
 }
 return min;
}
int maximum(int array[], int n)
{
  int max = array[0];
  for (int i = 1; i < n; i++)
  {
    if (array[i] > max)
      max = array[i];
  }
  return max;
}
int range(int array[], int n)
{
  return array[n-1] - array[0];
}

double average(int array[], int n)
{
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum+= array[i];
  return (double)sum / n;
}
double median(int array[], int n)
{
  int index;
  if (n % 2 != 0)
  {
    index = (n/2);
    return array[index];
  }
  else{
    index = ((n / 2) - 1); 
    return (double)(array[index] + array[index + 1]) / 2;
  }
}
double stddev(int array[], int n)
{
  double mu = average(array, n);
  double sum{0};

  for (int i = 0; i < n; i++) 
  {
    sum+= (double)((array[i] - mu) * (array[i] - mu));
  }
  double stdev = sqrt(sum / n);

  return stdev;
}
