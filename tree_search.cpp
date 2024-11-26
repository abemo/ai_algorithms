// https://www.geeksforgeeks.org/binary-tree-in-cpp/ 

#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

template <typename T>
class Node {
public:
  T data;
  Node* left;
  Node* right;
  Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree {
private:
    Node<T>* root;

    Node<T>* deleteRecursive(Node<T>* current, T value) {
    if (current == nullptr) return nullptr;

    if (current->data == value) {
        if (current->left == nullptr && current -> right == nullptr) {
            delete current;
            return nullptr;
        }
        if (current->left == nullptr) {
            Node<T>* temp = current->right;
            delete current;
            return temp;
        }
        if (current->right == nullptr) {
            Node<T>* temp = current->left;
            delete current;
            return temp;
        }
        Node<T>* successor = findMin(current->right);
        current->data = successor->data;
        current->right = deleteRecursive(current->right, successor->data);
    } else {
        current->left = deleteRecursive(current->left, value);
        current->right = deleteRecursive(current->right, value);
    }
    return current;
    }

    Node<T>* findMin(Node<T>* node) {
    while (node->left != nullptr) { node = node->left; }
    return node;
    }

    bool depthFirstSearch(Node<T>* current, T target) {
        stack<Node<T>*> s;
        unordered_set<Node<T>*> visited;
        s.push(root);

        while (!s.empty()) {
            Node<T>* current = s.top();
            s.pop();
            if (current->data == target) return 1;
            visited.insert(current);
            if (current->left != nullptr) s.push(current->left);
            if (current->right != nullptr) s.push(current->right);
        }
        return 0;
    }

public:
    BinaryTree() : root(nullptr) {}

    void insertNode(T value) {
    Node<T>* newNode = new Node<T>(value);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    queue<Node<T>*> q;
    q.push(root);

    while (!q.empty()) {
        Node<T>* current = q.front();
        q.pop();

        if (current->left == nullptr) {
            current->left = newNode;
            return;
        } else {
            q.push(current->left);
        }

        if (current->right == nullptr) {
            current->right = newNode;
            return;
        } else {
            q.push(current->right);
        }
    }
    }

    void deleteNode(T value) {
        root = deleteRecursive(root, value);
    }

    bool dfs(T target) {
        return depthFirstSearch(root, target);
    }
};


int main() {
    BinaryTree<int> tree;

    tree.insertNode(1);
    tree.insertNode(2);
    tree.insertNode(3);
    tree.insertNode(4);
    tree.insertNode(5);
    tree.insertNode(6);
    tree.insertNode(7);

    cout << "Does tree have value 6? " << tree.dfs(6) << "\n";
    cout << "Deleting 6 from tree.\n";
    tree.deleteNode(6);
    cout << "Does tree have value 6? " << tree.dfs(6) << "\n";
    return 0;
}