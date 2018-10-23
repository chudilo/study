class BinaryTreeNode{
public:
  int value;
  BinaryTreeNode *left_child;
  BinaryTreeNode *right_child;
  void insert(int val);
  void print();
  BinaryTreeNode(int val);
};

class BinaryTree{
public:
  BinaryTreeNode *head;

  //void insert(int val);
  void insert(int val);
  void print();
  BinaryTree();

};

void bubbleSort(int *vect, int size);

void combSort(int *sort, int size);
