// 240 Daily - Insert into Sorted

#include <iostream>
#include <iomanip>

using namespace std;


void print_arrays(int [], int, int [], int);
int insert_into_sorted(int [], int, int [], int);


int main()
  {
  int test_num;

  //Determine which test to run
  cout << "Test Number? ";
  cin >> test_num;

  if(test_num == 1)
    {
    int A1[2] = {10, 20},
        B1[3],
        new_elem1 = 15;

	//Test inserting in the middle of the array
    insert_into_sorted(A1, 2, B1, new_elem1);

    print_arrays(A1, 2, B1, new_elem1);
	}
  else if(test_num == 2)
    {
    int A2[3] = {10, 20, 30},
        B2[4],
        new_elem2 = 5;
			
	//Test inserting at the beginning of the array
    insert_into_sorted(A2, 3, B2, new_elem2);

    print_arrays(A2, 3, B2, new_elem2);
	}
  else if(test_num == 3)
    {
    int A3[6] = {10, 20, 40, 80, 160, 320},
        B3[7],
        new_elem3 = 640;
			
    //Test inserting at the end of the array
    insert_into_sorted(A3, 6, B3, new_elem3);

    print_arrays(A3, 6, B3, new_elem3);
	}
  else if(test_num == 4)
    {
    int A4[9] = {-42, -37, -33, -21, 0, 4, 67, 89, 112},
        B4[10],
        new_elem4 = -5;
			
    //Test inserting in the middle of the array
    insert_into_sorted(A4, 9, B4, new_elem4);

    print_arrays(A4, 9, B4, new_elem4);
	}
  else if(test_num == 5)
    {
    int A5[10] = {-5, -2, 4, 18, 23, 54, 73, 89, 91, 99},
        B5[11],
        C5[12],
        new_elem5b = 1,
        new_elem5c = 115;
			
    //Test inserting two numbers in the array
    
    //Add the 1st number
    insert_into_sorted(A5, 10, B5, new_elem5b);

    print_arrays(A5, 10, B5, new_elem5b);

    cout << endl;

    //Add the 2nd number
    insert_into_sorted(B5, 11, C5, new_elem5c);

    print_arrays(B5, 11, C5, new_elem5c);
	}
  else
    {
    int A6[4] = {10, 20, 40, 80},
        B6[5] = {0},
        new_elem6 = 42,
        ret_value;

    //Try inserting a value when the array size is invalid
    ret_value = insert_into_sorted(A6, -4, B6, new_elem6);

    //Display the arrays
    print_arrays(A6, 4, B6, new_elem6);
  
    //Determine if the function was successful or failed
    if( ret_value == 0 )
      {
      cout << endl << "SUCCESS - the function detected the length error" << endl;
      }
    else
      {
      cout << endl << "FAILURE - the function DID NOT detect the length error" << endl;
      }
	}

  return 0;
  } /* end main() */


//This function prints the value that is supposed to be inserted into
//the second array, the contents of the original array (A), and the contents
//of the new array (B)
void print_arrays(int A[], int len_A, int B[], int new_elem)
  {
  int i;

  //Display the value that is to be inserted into the correct sorted position
  cout << endl << "The inserted value " << new_elem << endl << endl
       << "The original array contains {";

  //Display the values in the orginal array
  for (i = 0; i < len_A-1; i ++)
    {
    cout << A[i] << ", ";
    }

  cout << A[len_A-1] << "}" << endl << "The new array contains      {";
	
  //Display the values in second array
  for (i = 0; i < len_A; i ++)
    {
    cout << B[i] << ", ";
    }
		
  cout << B[len_A] << "}" << endl;
  } // end print_arrays()
  
// This function takes a sorted array, and inserts any one value into the sorted list in the correct position such that the list stays sorted
/*
 * Notes: Need to first find the target index, 
 * then need to copy the values from the sorted array into the new array with the new element falling inbetween such that A[i] < x < A[i+1]
 * Side notes: if the new_elem is less than the value at the starting index it should be placed at the starting index. same goes with the value at the last index; else: ** find A[i] < x < A[i + 1], grab index at i + 1 **
 *  ****** while making new array, account for mismatching index values after inserting new elem ****
 */
int insert_into_sorted(int source[], int source_len, int destination[], int new_elem){
  int target_index, new_length = source_len +1;
  if (source_len < 0){
    return 0;
  }
  else{
    if (new_elem < source[0]){
      target_index = 0;
    }
    else if (new_elem > source[source_len -1]){
      target_index = source_len;
    }
    else{
      for (int i = 0; i < source_len; i++){
        if (new_elem > source[i] && new_elem < source[i + 1]){
          target_index = i + 1;
        }
      }
    }
    for (int i = 0; i < new_length; i++){
     if (i == target_index){ // new_elem belongs at this index
        destination[i] = new_elem;
      } 
      else if (i < target_index){ // both indexs match, can copy using the same index
        destination[i] = source[i];
      }
      else{
        destination[i] = source[i - 1]; // since the new value is inserted, the indexs no longer match, source is one behind
      }
    }
  }
  return 1;
}
