// int a[] = an array of integer elements representing 
// the lengths of the pieces of rope tied to the rod.
//
// n = the number of pieces of rope tied to the rod
//
// sum = the sum of the lengths of the pieces that you need to cut away.
int cutting_rope(int a[], int n, int sum)
{
  // find the max_distance
  int maxDistance = a[0];
  for (int i = 1; i < n; i++)
  {
    if (a[i] > maxDistance)
      maxDistance = a[i];
  }
  //loop through all possible cut distances
  for (int j = 0; j < maxDistance; j++)
  {
    int newLength;
    int testSum = 0;

    // loop through each piece of rope
    for (int k = 0; k < n; k++)
    {
      if (a[k] - j <= 0) 
        newLength = 0;
      else
        newLength = (a[k] - j);

      testSum+=newLength;
    }
      // add to sum
  if (testSum == sum)
    return j;
  }
  return -1;
}
// loop through every distance scenario
// loop through all the elements in the arary
// add to sum by finding the length of the rope with respect to the cut made (length - distance)
// if sum == sum, return 1
