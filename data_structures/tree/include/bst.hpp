// bst.hpp
#pragma once
#include <iostream>
#include <memory>
#include <stack>

#include "logger.hpp"

template <typename T>
class BinarySearchTree {
   private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(T value) : data(value) {
            Logger::Debug("Node created with value: " + std::to_string(data));
        }

        ~Node() {
            Logger::Debug("Node destoyed with value: " + std::to_string(data));
        }
    };

    std::unique_ptr<Node> root_;
    std::stack<Node*> stack;

   public:
    BinarySearchTree() { Logger::Debug("BST created."); };

    ~BinarySearchTree() { Logger::Debug("BST destroyed."); }

    void insert(T value) {
        Logger::Debug("Inserting value: " + std::to_string(value));
        insertImpl(root_, value);
    }

   private:
    void insertImpl(std::unique_ptr<Node>& node, T value);
};

template <typename T>
void BinarySearchTree<T>::insertImpl(std::unique_ptr<Node>& node, T value) {
    Logger::Debug("Start insertImpl for value: " + std::to_string(value));
    if (!node) {
        Logger::Debug("Tree is empty. Creating root node with value: " +
                      std::to_string(value));
        node = std::make_unique<Node>(value);
        return;
    }

    Node* current = node.get();

    while (true) {
        std::string current_val = std::to_string(current->data);

        if (value < current->data) {
            Logger::Debug("Value " + std::to_string(value) +
                          " < current node " + current_val);

            if (!current->left) {
                Logger::Debug("Left child of node " + current_val +
                              " is empty. Inserting there.");

                current->left = std::make_unique<Node>(value);
                Logger::Debug("Inserted " + std::to_string(value) +
                              " as left child of " + current_val);
                break;
            } else {
                Logger::Debug("Node " + current_val +
                              " has left child. Moving left.");
                current = current->left.get();
            }
        } else if (value > current->data) {
            Logger::Debug("Value " + std::to_string(value) +
                          " > current node " + current_val);
            if (!current->right) {
                Logger::Debug("Right child of node " + current_val +
                              " is empty. Inserting there.");
                current->right = std::make_unique<Node>(value);
                Logger::Debug("Inserted " + std::to_string(value) +
                              " as right child of " + current_val);
                break;
            } else {
                Logger::Debug("Node " + current_val +
                              " has left child. Moving right.");
                current = current->right.get();
            }
        } else {
            Logger::Debug("Value " + std::to_string(value) +
                          " already exists in tree. Insertion skipped.");
            break;
        }
    }
}