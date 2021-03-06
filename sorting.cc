//
//This file does not consider digital sorting algorithms (i.e.: radix sorting)
//They split the key in a sequence of bytes (or group of bytes) and, starting
//from the first one until the last sort the list according to it. In other
//words, the array is sorted with respect to the first byte, than each group
//is sorted independently according to the second byte and so on

#include <iostream>
#include <assert.h>

using namespace std;

template<class T>
void exchange(T* a, T* b) {
  T c = *a;
  *a = *b;
  *b = c;
}

//it aims at moving at the index i-th the minimum value from i+1 to the last
//pros:
//- simple
//- space complexity O(1)
//cons:
//- complexity O(N^2) (N^2/2 comparisons and N exchanges)
//- if the array is already sorted, the performance does not improve
template<class T>
void selection_sort(T a[], int N) {
  for (int i = 0; i < (N-1); i++) {
    int min = i;
    for (int j = i+1; j < N; j++)
      if (a[j] < a[min])
        min = j;
    exchange(&a[i], &a[min]);
  }
}

//it puts at position i-th an element which is greater than the previous ones
//if i=5 and a[3] is grater than a[2], it does not check a[1] and a[0] as it
//already knows that the original a[5] was not lower than a[2], a[1] and a[0]
//it a[8] is the smallest, that it is the only one which will reach a[0]
//pros:
//- simple
//- if the array is partially sorted, many checks are skipped
//- space complexity O(1)
//cons:
//- complexity in the worst case O(N^2) (N^2/4 comparisons and N^2/4 exchanges)
template<class T>
void insertion_sort(T a[], int N) {
  for (int i = 1; i < N; i++) {
    int j = i;
    while (j > 0 && a[j] < a[j-1]) {
      exchange(&a[j], &a[j-1]);
      j--;
    }
  }
}

//adjacent nodes are exchanges and the biggest one is pushed until the latest
//position
//pros:
//- simple
//- space complexity O(1)
//cons:
//- slower than the insertion and selection sorts
//- complexity O(N^2) (N^2/2 comparisons and N^2/2 exchanges)
template<class T>
void bubble_sort(T a[], int N) {
  for (int i = 0; i < (N-1); i++)
    for (int j = i+1; j < N; j++)
      if (a[i]>a[j])
        exchange(&a[i], &a[j]);
}

//shell sort is a variant of insertion sort working of element with distance h.
//the distance is gradually reduced after each iteration of the insertion sort.
//Since it starts working with few elements (high h), the single instances are
//short (there are many h-sequences)
//the complexity is O(N^4/3) o O(N^3/2) with respect to the sequence in use
//cons:
//- it is not easy to study its performance
template<class T>
void shell_sort(T a[], int N) {
  int h = 0;
  for (; h < N/9; h += 3*h+1); //compute the highest h
  for (; h>0; h /= 3) {
    for (int i = h; i < N; i++) {
      int j = i;
      while (j >= h && a[j] < a[j-h]) {
        exchange(&a[j], &a[j-h]);
        j -= h;
      }
    }
  }
}

template<class T>
int quick_sort_partition(T a[], int start, int stop) {
  T v = a[stop];
  int i_low = start, i_up = stop-1;
  for (;;) {
    while(a[i_low] < v) i_low++;
    while(v < a[i_up]) i_up--;
    if (i_low >= i_up)
      break;
    exchange(&a[i_low], &a[i_up]);
  }
  exchange(&a[i_low], &a[stop]);
  return i_low;
}

//quick sort relies on the divide and empire approach
//the assumption is: pick a number and place it in the right place (the elements
//in the right side are lower, while the ones in the left side are higher)
//in the average case its complexity is O(N logN), in the worst it is O(N^2)
//other approach for picking the element to partition can be used (even
//statistical)
//many equal values make the algorithm slow
template<class T>
void quick_sort(T a[], int start, int stop) {
  if (start >= stop)
    return;
  int i = quick_sort_partition(a, start, stop);
  quick_sort(a, start, i-1);
  quick_sort(a, i+1, stop);
}

template<class T>
void merge (T a[], int start, int center, int stop) {
  int size = stop-start+1;
  T *tmp = new T[size];
  for (int i = start, j = center+1, k = 0; k < size; k++) {
    if (i > center) {
      tmp[k] = a[j++];
      continue;
    }
    if (j > stop) {
      tmp[k] = a[i++];
      continue;
    }
    tmp[k] = (a[i] < a[j]) ? a[i++] : a[j++];
  }
  for (int i = 0; i < (stop-start+1); i++)
    a[i+start] = tmp[i];
  delete[] tmp;
}

//(top-down) merge sort relies on divide-and-conquer approach: it divides the
//array in two parts (recursively), than merge in a sorted way two adjacent
//parts
//it is always O(N logN) (N logN comparisons) and it does not depend on the
//initial order
//space complexity is around O(N)
template <class T>
void merge_sort(T a[], int start, int stop) {
  if (stop <= start)
    return;
  int m = (stop+start)/2;
  merge_sort(a, start, m);
  merge_sort(a, m+1, stop);
  merge(a, start, m, stop);
}

template<class T>
void fixDown(T a[], int k, int N) {
  //k-th node's sons are at position 2*k and 2*k+1
  while((2*k) < N) {
    int son = 2*k;
    //pick son which highest priority
    if (son < (N-1) && a[son] < a[son+1])
      son++;
    if (a[k] >= a[son])
      break;
    exchange(&a[k], &a[son]);
    k = son;
  }
}

//the heap sort algorithm modifies the actual array to become a heap
//The prodedure requires less than 2N logN comparisons
//The time complexity is O(NlogN) and the space complexity is O(1)
//Creating a heap by scratch is more expensive in terms of space
//complexity
//Like the mergesort, the heap sort is not stable
template<class T>
void heap_sort(T a[], int N) {
  int k = 0;
  //build the heap
  for (k = N/2 - 1; k >= 0; k--)
    fixDown(a, k, N);
  //sort the array from smallest to highest by retreiving the max
  while(N > 1) {
    exchange(&a[0], &a[N-1]);
    N--;
    fixDown(a, 0, N);
  }
}

#define ARRAY_SIZE 20

int main () {
  for (int i = 0; i < 7; i++) {
    int ar[ARRAY_SIZE] = {3, 20, 1, 19, 8, 5, 13, 10, 18, 7, 12, 9, 14, 4, 2,
                          15, 6, 17, 11, 16};
    switch(i) {
      case 0:
        selection_sort(ar, ARRAY_SIZE);
        break;
      case 1:
        bubble_sort(ar, ARRAY_SIZE);
        break;
      case 2:
        insertion_sort(ar, ARRAY_SIZE);
        break;
      case 3:
        shell_sort(ar, ARRAY_SIZE);
        break;
      case 4:
        quick_sort(ar, 0, ARRAY_SIZE-1);
        break;
      case 5:
        merge_sort(ar, 0, ARRAY_SIZE-1);
        break;
      case 6:
        heap_sort(ar, ARRAY_SIZE);
        break;
      default:
        break;
    };
    for (int j = 0; j < ARRAY_SIZE; j++)
      assert(ar[j]==(j+1));
  }

  return 0;
}
