int find_summit(int a[], int len)
{
  if (len == 1) // Edge case
    return a[0];

  int summit;
  int isSummit;

  for (int i = 0; i < len; i++)
  {
    isSummit = true;
    int j = i - 1;
    int k = i + 1;

    while (j >= 0 || k < len)
    {
      if (j >= 0) 
      {
        if (a[j] > a[i])
        {
          isSummit = false;
          break;
        }
      }
      j--;

      if (k < len)
      {
        if (a[k] > a[i])
        {
          isSummit = false;
          break;
        }
      }
      k++;
    }
    if (isSummit)
      summit = a[i];
  }
  return summit;
}
// VARS -> summit: the summit value in a[]
//         isSummit: tells us if the current index passed all checks after breaking out of the inner loop
// TEMPS -> i, j, k
//
// NEED: 
// an outer loop that goes through each element in the array
// an inner loop that is both one behind and one ahead of current index, compares each value
// if condition is false; break out of the loop and set isSummit to false
// else, simply continue the iterations
//
