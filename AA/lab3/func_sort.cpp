//#include "matrix_func.h"
template <typename T>
void bubbleSort(vector<T> &vect) {
  int vsize = vect.size() - 1;
  for(int i = 0; i < vsize; i++)
    for(int j = 0; j < vsize - i; j++) {
      if(vect[j] > vect[j+1]) {
          T temp = vect[j];
          vect[j] = vect[j+1];
          vect[j+1] = temp;
      }
    }

}

template <typename T>
void combSort(vector<T> &sort)
{
  int n = 0; // количество перестановок
  double fakt = 1.2473309; // фактор уменьшения
  double step = sort.size() - 1;

  while (step >= 1) {
    for (int i = 0; i + step < sort.size(); ++i)
      if (sort[i] > sort[i + step])
        swap(sort[i], sort[i + step]);

    step /= fakt;
  }

  for (int i = 0; i < sort.size() - 1; i++) {
    bool swapped = false;
    for (int j = 0; j < sort.size() - i - 1; j++)
      if (sort[j] > sort[j + 1]) {
        swap(sort[j], sort[j + 1]);
        swapped = true;
      }

    if (!swapped)
      break;
  }
}

#include <memory>
#include <cassert>
#include <algorithm>

#include <vector>
#include <iostream>

using namespace std;

// класс, представляющий бинарное дерево
class BinaryTree
{
protected:
  // узел бинарного дерева
  struct BinaryTreeNode
  {
    shared_ptr<BinaryTreeNode> left, right; // левое и правое поддерево
    int key; // ключ
  };

  shared_ptr<BinaryTreeNode> m_root; // корень дерева

protected:
  // рекурсивная процедура вставки ключа
  // cur_node - текущий узел дерева, с которым сравнивается вставляемый узел
  // node_to_insert - вставляемый узел
  void insert_recursive(const shared_ptr<BinaryTreeNode>& cur_node, const shared_ptr<BinaryTreeNode>& node_to_insert)
  {
      assert(cur_node != nullptr);
      // сравнение
      bool insertIsLess = node_to_insert->key < cur_node->key;
      if(insertIsLess)
      {
        // вставка в левое поддерево
        if(cur_node->left == nullptr)
          cur_node->left = node_to_insert;
        else
          insert_recursive(cur_node->left, node_to_insert);
      }
      else
      {
        // вставка в правое поддерево
        if(cur_node->right == nullptr)
          cur_node->right = node_to_insert;
        else
          insert_recursive(cur_node->right, node_to_insert);
      }
  }

public:
  void insert(int key)
  {
    shared_ptr<BinaryTreeNode> node_to_insert(new BinaryTreeNode);
    node_to_insert->key = key;

    if(m_root == nullptr)
    {
        m_root = node_to_insert;
        return;
    }

    insert_recursive(m_root, node_to_insert);
  }

public:
  typedef function<void(int key)> Visitor;

protected:
  // рекурсивная процедура обхода дерева
  // cur_node - посещаемый в данный момент узел
  void visit_recursive(const shared_ptr<BinaryTreeNode>& cur_node, const Visitor& visitor)
  {
    assert(cur_node != nullptr);

    // сначала посещаем левое поддерево
    if(cur_node->left != nullptr)
      visit_recursive(cur_node->left, visitor);

    // посещаем текущий элемент
    visitor(cur_node->key);

    // посещаем правое поддерево
    if(cur_node->right != nullptr)
      visit_recursive(cur_node->right, visitor);
  }

public:
  void visit(const Visitor& visitor)
  {
    if(m_root == nullptr)
      return;
    visit_recursive(m_root, visitor);
  }
};


int main()
{
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

  // результат выполнения: 2 3 7 7 10 14 32
  return 0;
}
/*
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;
#include <cstdio>

//#include "matrix_func.h"
#include "get_time.h"

//#define SIZE 1000
#define TIMES 10

int main() {

	for(int i = 0; i < 20; i++) {
		int SIZE = 100 + i*100;

		double t1, t2, restimeMult = 0, restimeVin = 0, restimeVinUpgr = 0;

		for(int j = 0; j < TIMES; j++) {

			t1 =  getCPUTime( );

			t2 =  getCPUTime( );

			restimeMult += (t2-t1);

		}

		printf("Proc time for %d elements casual mult :\n%f\n", SIZE, restimeMult/TIMES);
		printf("Proc time for %d elements Vinograd mult :\n%f\n", SIZE, restimeVin/TIMES);
		printf("Proc time for %d elements upgrade Vinograd mult:\n%f\n",SIZE, restimeVinUpgr/TIMES);
		puts("");

	}
}
*/
