#include <cstdio>
#include <cstdlib>
#include <algorithm>    // std::swap
#include <iostream>


#include <vector>
#include <ctime>

using namespace std;

#include "get_time.h"
#include "func_sort.h"

#define TIMES 100

int main() {
	std::srand(std::time(0)); //use current time as seed for random generator

	for(int i = 0; i < 10; i++) {
		int vsize = 1000 + i*1000;
    double t1, t2, result_bubble = 0, result_comb = 0, result_tree = 0;

    for(int i = 0; i < TIMES; i++) {
  		//vector<int> v_orig(vsize), v_sorted(vsize);

      int *arr = new int [vsize];
      int *v_sorted = new int[vsize];

  		for(int i = 0; i < vsize; i++)
  			arr[i] = std::rand()%1000;

      for(int i = 0; i < vsize; i++)
        v_sorted[i]= arr[i];
      t1 = getCPUTime();
  		bubbleSort(v_sorted, vsize);
      t2 = getCPUTime();
      //printf("bubble sort for %d el is %f\n",vsize, t2-t1);
      result_bubble += t2-t1;

      for(int i = 0; i < vsize; i++)
        v_sorted[i]= arr[i];
      t1 = getCPUTime();
      combSort(v_sorted, vsize);
      t2 = getCPUTime();
      //printf("comb sort for %d el is %f\n",vsize, t2-t1);
      result_comb += t2-t1;


      BinaryTree tree;
      t1 = getCPUTime();
      for(int i = 0; i < vsize; i++)
        tree.insert(arr[i]);
      t2 = getCPUTime();
      result_tree += t2-t1;

      delete arr;
      delete v_sorted;
    }
    printf("bubble sort for %d el is %f\n",vsize, result_bubble/TIMES);
    printf("comb sort for %d el is %f\n",vsize, result_comb/TIMES);
    printf("tree sort for %d el is %f\n",vsize, result_tree/TIMES);
  }
}
/*
  BinaryTree tree;
  // добавление элементов в дерево
  vector<int> data_to_sort = {10, 2, 7, 3, 14, 7, 32};
  for(int value : data_to_sort)
  {
    tree.insert(value);
  }
  // обход дерева
  tree.visit([](int visited_key)
  {
    cout<<visited_key<<" ";
  });
  cout<<endl;
*/
