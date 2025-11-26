#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int val) {
        if (find(val)) return;
        root = insert(root, val);
    }

    Node* find(int val) const {
        return findRec(root, val);
    }

    void buildFromSortedArray(const std::vector<int>& arr) {
        destroy(root);
        if (arr.empty()) return;
        std::vector<int> temp = arr;
        temp.erase(std::unique(temp.begin(), temp.end()), temp.end());
        root = buildFromSortedArray(temp, 0, temp.size() - 1);
    }

    void printInOrder() const {
        printInOrder(root);
        std::cout << std::endl;
    }

private:
    Node* root;

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data) node->left = insert(node->left, val);
        else if (val > node->data) node->right = insert(node->right, val);
        return node;
    }

    Node* findRec(Node* node, int val) const {
        if (!node) return nullptr;
        if (node->data == val) return node;
        if (val < node->data) return findRec(node->left, val);
        return findRec(node->right, val);
    }

    Node* buildFromSortedArray(const std::vector<int>& arr, int start, int end) {
        if (start > end) return nullptr;
        int mid = start + (end - start) / 2;
        Node* node = new Node(arr[mid]);
        node->left = buildFromSortedArray(arr, start, mid - 1);
        node->right = buildFromSortedArray(arr, mid + 1, end);
        return node;
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void printInOrder(Node* node) const {
        if (!node) return;
        printInOrder(node->left);
        std::cout << node->data << " ";
        printInOrder(node->right);
    }
};