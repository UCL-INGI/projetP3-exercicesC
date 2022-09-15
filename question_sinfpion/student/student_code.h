typedef struct Node {
  int value;
  struct Node* next;
} node_l;

int findMinIndex(node_l* head);

int removeTheMinIndex(node_l ** head, int MinIndex);
