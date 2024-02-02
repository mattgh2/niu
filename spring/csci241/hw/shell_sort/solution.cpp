void shell_sort(int array[], int n)
{

int g = 0;
int i, j;
int gap;
int temp;

// ciura gap sequence
int gaps[8] = {701, 301, 132, 57, 23, 10, 4, 1}; 

while (g < 8)
{
  gap = gaps[g];

  i = gap;

  while (i < n)
  {
    temp = array[i];

    j = i;

    while (j >= gap && array[j - gap] > temp)
    {
      array[j] = array[j - gap];
      j = j - gap;
    }
    
    array[j] = temp;

    i++;
  }
  g++;
}

}
