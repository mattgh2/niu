int sum_odd_elements(int a[], int n)
{
  int sum = 0;

  if (n == 1)
    return 0;
  
  for (int i = 1; i < n;i+=2)
  {
   sum+= a[i];
  }

  return sum;
}
