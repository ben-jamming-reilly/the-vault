/*
Ben Reilly 
Eric Gustin
Brian Steuber
Chris Fergueson 

Implements Stooge, Worse, Cocktail, & Ben Sort
along with a basic testing frame-work
*/

#include "proj3.h"

//=============================================================
//
//                     Testing Framework
//
//=============================================================

void run_test(const string &file_name, void (*sort)(int *arr, int n))
{
   //Load Array
   int *arr = nullptr;
   int n = -1;
   arr = file_to_array(file_name, n);
   if(arr == nullptr)
   {
      cout<<"ERROR... file did not load"<<endl;
      return;
   }
   
   //Time Test
   using namespace std::chrono;
   
   high_resolution_clock::time_point start = high_resolution_clock::now();
   sort(arr, n);
   high_resolution_clock::time_point stop = high_resolution_clock::now();
   
   //micro-seconds
   auto duration_us = duration_cast<microseconds>(stop - start);
   //milli-seconds
   auto duration_ms = duration_cast<milliseconds>(stop - start);
   //seconds
   auto duration_s = duration_cast<seconds>(stop - start);
   
   cout<<"  N = "<<n<<"\n";
   cout<<"  <> microseconds\t"<<duration_us.count()<<"\n";
   cout<<"  <> milliseconds\t"<<duration_ms.count()<<"\n";
   cout<<"  <> seconds     \t"<<duration_s.count()<<"\n\n";
   
   //Success Test
   if(!is_sorted(arr, n))
      cout<<"Failure -- unsorted list"<<endl;
   
   delete[] arr;
}

int* file_to_array(const string &file_name, int &n)
{
   fstream in_file;
   in_file.open(file_name.c_str());
   
   int arr_len;
   int *arr_ptr = nullptr;
   
   //File Length at top of file;
   if(in_file)
      in_file>>arr_len;
   else
      return nullptr;
   
   arr_ptr = new int[arr_len];
   
   int i = 0;
   while(in_file)
   {
      int num;
      in_file>>num;
      arr_ptr[i] = num;
      i++;
   }
   
   n = arr_len;
   return arr_ptr;
}

bool is_sorted(int *arr, int n)
{
   for(int i = 1; i < n; i++)
      if(arr[i - 1] > arr[i])
         return false;
   return true;
}

//=============================================================
//
//                     Sorting Algorithms
//
//=============================================================


//------------------------Stooge_Sort------------------------//
void stooge_sort(int *arr, int n)
{
   stooge_sort(arr, 0, n - 1);
}

void stooge_sort(int arr[], int first, int last)
{
   int tmp; // temp variable for swap
   if (first >= last) // base case
      return; 
   if (arr[first] > arr[last]) // first > last
   {
      // swap  
      tmp = arr[first];
      arr[first] = arr[last];
      arr[last] = tmp;
   }
   if (last - first + 1 > 2) // size > 2
   {
      int stooge = (last - first + 1) / 3; 
      // sort first 2/3 of array
      stooge_sort(arr, first, last - stooge);
      // sort last 2/3 of array
      stooge_sort(arr, first + stooge, last);
      // sort first 2/3 to confirm sorting
      stooge_sort(arr, first, last - stooge);
  }
}

//------------------------Worse_Sort-------------------------//

void worse_sort(int *arr, int n)
{
   int **arr_arr = nullptr;
   int fact_n = factorial(n);
   
   arr_arr = generate_perm(arr, n); //calc all permutations
   lex_bubble_sort(arr_arr, fact_n, n); //Sorts permutations
   
   //copy the value
   for(int i = 0; i < n; i++)
      arr[i] = arr_arr[0][i];
   
   //deallocate memory
   for(int i = 0; i < fact_n; i++)
      delete[] arr_arr[i];
   delete[] arr_arr;
}

int** generate_perm(int *arr, int n)
{
   int fact_n = factorial(n);
   int **lst_arr = new int*[fact_n];
   
   for(int i = 0; i < fact_n; i++)
   {
      lst_arr[i] = new int[n];
   }
   
   recur_generate_perm(lst_arr, 0, arr, 0, n - 1);
   return lst_arr;
}

void recur_generate_perm(int **arr_arr, int arr_arr_i, int *arr, int l, int r)
{
   if(l == r)
   {
      for(int i = 0; i <= r; i++)
         arr_arr[arr_arr_i][i] = arr[i];
   }
   else
   {
      int t = factorial(r - l);
      
      for(int i = l; i <= r; i++)
      {
         int sto;
         sto = *(arr + l);
         *(arr + l) = *(arr + i);
         *(arr + i) = sto;
         
         recur_generate_perm(arr_arr, arr_arr_i, arr, l + 1, r);
         arr_arr_i += t;
         
         sto = *(arr + l);
         *(arr + l) = *(arr + i);
         *(arr + i) = sto;
         
      }
   }
}

void lex_bubble_sort(int **arr_arr, int fact_n, int n)
{
   for(int i = 0; i < fact_n-1; i++)
   {
      for(int j = 0; j < fact_n-i-1; j++)
      {
         int *sto;
         if(lex_greater_than(arr_arr[j], arr_arr[j+1], n))
         {
            sto = arr_arr[j];
            arr_arr[j] = arr_arr[j+1];
            arr_arr[j+1] = sto;
         }
      }
   }
}

bool lex_greater_than(int *lhs_arr, int *rhs_arr, int n)
{
   for(int i = 0; i < n; i++)
   {
      if(lhs_arr[i] < rhs_arr[i])
         return false;
      else if(lhs_arr[i] > rhs_arr[i])
         return true;
   }
   return false;
}

int factorial(int n)
{
   if(n == 0)
      return 1;
   else
      return n * factorial(n - 1);
}

//----------------------Cocktail_Sort------------------------//

void cocktail_sort(int arr[], int arr_size)
{
   int temp_element; // used as a temporary placeholder when doing swaps
   int unsorted_begin = 0;
   int unsorted_end = arr_size - 1;
   bool unsorted = true;
   
   while (unsorted)
   {
      unsorted = false;
   
      // do an iteration of bubble sort 
      for (int i = unsorted_begin; i < unsorted_end; ++i)
      {
         if (arr[i] > arr[i+1])
         {
            // do swap
            temp_element = arr[i+1];
            arr[i+1] = arr[i];
            arr[i] = temp_element;
            unsorted = true;
         }
      }
  
      --unsorted_end; // sorted region increased by 1
      
      // no swap occurred which means that the array is sorted
      if (!unsorted)
         break;

      // if a swap occurred, then reset move to false so that backwards bubblesort can begin
      unsorted = false;

      //do an iteration of backwards bubblesort
      for (int i = unsorted_end-1; i >= unsorted_begin; --i)
      {
         if (arr[i] > arr[i+1])
         {
            // do swap
            temp_element = arr[i+1];
            arr[i+1] = arr[i];
            arr[i] = temp_element;
            unsorted = true;
         }
      }
      ++unsorted_begin; // sorted region increased by one
   }
}


//-------------------------Ben_Sort--------------------------//

void ben_sort(int *arr, int n)
{
   int max = 0, min = 0;
   get_high_low(arr, n, max, min);
   hash_arr(arr, n, max, min);
   insertion_sort(arr, n);
}

void insertion_sort(int *arr, int n) 
{
   for (int i = 1; i < n; i++) 
   {  
      int key = arr[i];  
      int j = i - 1;  
  
      while (j >= 0 && arr[j] > key) 
      {  
         arr[j + 1] = arr[j];  
         j--;  
      }  
      arr[j + 1] = key;  
    }  
} 

void hash_arr(int *arr, int n, int max, int min)
{
   bool *b_arr = new bool[n];
   int  *map_arr = new int[n];
   
   for(int i = 0; i < n; i++)
      b_arr[i] = false;
   
   for(int i = 0; i < n; i++)
   {
      int index = map_func(arr[i], n, max, min);
      
      if(!b_arr[index])
      {
         map_arr[index] = arr[i];
         b_arr[index] = true;
      }
      else
      {
         int dir = 0;
         
         if(map_arr[index] > arr[i])
            dir = n-1;
         else
            dir = 1;
         
         while(!b_arr[index])
            index = (index + dir) % n;
         
         map_arr[index] = arr[i];
         b_arr[index] = true;
      }
   }
   arr = map_arr;
   delete[] arr;
   delete[] b_arr;
}

void get_high_low(int *arr, int n, int &max, int &min)
{
   int high = arr[0],
       low = arr[0];
       
   for(int i = 0; i < n; i++)
   {
      if(arr[i] > high)
         high = arr[i];
         
      if(arr[i] < low)
         low = arr[i];
   }
   max = high;
   min = low;
}

int map_func(int data, int n, int max, int min)
{
   if(data == max)
      return n - 1;
   if(data == min)
      return 0;
   return n - (n * ((float)(max-min) - (data - min)) / (float)(max-min));
}