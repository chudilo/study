#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#include "func_sort.h"

void bubbleSort(int *vect, int size) {
  int vsize = size - 1;
  for(int i = 0; i < vsize; i++)
    for(int j = 0; j < vsize - i; j++) {
      if(vect[j] > vect[j+1]) {
          int temp = vect[j];
          vect[j] = vect[j+1];
          vect[j+1] = temp;
      }
    }

}

void combSort(int *sort, int size)
{
  int n = 0; // количество перестановок
  double fakt = 1.2473309; // фактор уменьшения
  int step = size - 1;

  while (step >= 1) {
    for (int i = 0; i + step < size; ++i)
      if (sort[i] > sort[i + step])
        swap(sort[i], sort[i + step]);

    step /= fakt;
  }

  for (int i = 0; i < size - 1; i++) {
    bool swapped = false;
    for (int j = 0; j < size - i - 1; j++)
      if (sort[j] > sort[j + 1]) {
        swap(sort[j], sort[j + 1]);
        swapped = true;
      }

    if (!swapped)
      break;
  }
}

BinaryTreeNode::BinaryTreeNode(int val) {
  value = val;
  left_child = NULL;
  right_child = NULL;
}

void BinaryTreeNode::print() {
  if(left_child)
    left_child->print();

  printf("%d ", value);

  if (right_child)
    right_child->print();
}

void BinaryTreeNode::insert(int val){
  if(val > value)
    if(right_child)
      right_child->insert(val);
    else
      right_child = new BinaryTreeNode(val);
  else
    if(left_child)
      left_child->insert(val);
    else
      left_child = new BinaryTreeNode(val);
}

void BinaryTree::print() {
  if(head)
    head->print();
  else
    printf("tree is empty\n");

}

void BinaryTree::insert(int val){
  if (head == NULL) {
      head = new BinaryTreeNode(val);
  }
  else
    head->insert(val);
}

BinaryTree::BinaryTree() {
  head = NULL;
}
