#include <iostream>

enum Color {
    RED,
    BLACK
};
template <typename TypeKey, typename TypeData>
struct Node {
    TypeKey key;
    TypeData data;
    int height;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(const TypeKey& fkey, const TypeData& data) : key(fkey), data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};
template <typename TypeKey, typename TypeData>
class RedBlackTreeIterator {
public:
    RedBlackTreeIterator(Node<TypeKey, TypeData>* node) : current{ node } {}

    TypeData& operator*() { return current->data; }
    Node<TypeKey, TypeData>* operator->() { return current; }
    Node<TypeKey, TypeData>* getcurrent() { return current; }

    RedBlackTreeIterator<TypeKey, TypeData>& operator++() {
        current = successorHelper(current);
        return *this;
    }
    Node<TypeKey, TypeData>* minHelper(Node<TypeKey, TypeData>* node) const {
        if (node->left == nullptr) {
            return node;
        }
        else {
            return minHelper(node->left);
        }
    }
    Node<TypeKey, TypeData>* maxHelper(Node<TypeKey, TypeData>* node) const {
        if (node==nullptr || node->right == nullptr) {
            return node;
        }
        else {
            return maxHelper(node->right);
        }
    }
    bool operator==(const RedBlackTreeIterator<TypeKey, TypeData>& other) const {
        return current == other.current;
    }

    bool operator!=(const RedBlackTreeIterator<TypeKey, TypeData>& other) const {
        return current != other.current;
    }

private:
    Node<TypeKey, TypeData>* current;
    Node<TypeKey, TypeData>* successorHelper(Node<TypeKey, TypeData>* node) const {
        if (node->right != nullptr) {
            return minHelper(node->right);
        }
        Node<TypeKey, TypeData>* temp = node->parent;
        while (temp != nullptr && temp->parent != nullptr && temp->key != temp->parent->key) {
            temp = temp->parent;
        }
        if (temp==nullptr || node->key == maxHelper(temp)->key) {
            return nullptr;
        }
        Node<TypeKey, TypeData>* parent = node->parent;
        while (parent != nullptr && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }

        return parent;
    }
};
template<typename TypeKey, typename TypeData>
class RedBlackTree {
private:
    Node<TypeKey, TypeData>* root;

    void rotateLeft(Node<TypeKey, TypeData>* node) {
        Node<TypeKey, TypeData>* rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left != nullptr) {
            rightChild->left->parent = node;
        }
        rightChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = rightChild;
        }
        else if (node == node->parent->left) {
            node->parent->left = rightChild;
        }
        else {
            node->parent->right = rightChild;
        }
        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(Node<TypeKey, TypeData>* node) {
        Node<TypeKey, TypeData>* leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right != nullptr) {
            leftChild->right->parent = node;
        }
        leftChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = leftChild;
        }
        else if (node == node->parent->left) {
            node->parent->left = leftChild;
        }
        else {
            node->parent->right = leftChild;
        }
        leftChild->right = node;
        node->parent = leftChild;
    }
    void fixRemove(Node<TypeKey, TypeData>* node) {
        while (node->parent != nullptr && node->color == BLACK) {
            if (node == node->parent->left) {
                Node<TypeKey, TypeData>* sibling = node->parent->right;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateLeft(node->parent);
                    sibling = node->parent->right;
                }

                if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    sibling->color = RED;
                    node = node->parent;
                }
                else {
                    if (sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotateRight(sibling);
                        sibling = node->parent->right;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    rotateLeft(node->parent);
                    node = root;
                }
            }
            else if (node==node->parent->right){
                Node<TypeKey, TypeData>* sibling = node->parent->left;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateRight(node->parent);
                    sibling = node->parent->left;
                }

                if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                    sibling->color = RED;
                    node = node->parent;
                }
                else {
                    if (sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(sibling);
                        sibling = node->parent->left;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rotateRight(node->parent);
                    node = root;
                }
            }
            else {
                if (node->parent->left==nullptr) {
                    Node<TypeKey, TypeData>* sibling = node->parent->right;

                    if (sibling->color == RED) {
                        sibling->color = BLACK;
                        node->parent->color = RED;
                        rotateLeft(node->parent);
                        sibling = node->parent->right;
                    }

                    if ((sibling->left==nullptr && sibling->right==nullptr) || (sibling->left!=nullptr && sibling->right!=nullptr && sibling->left->color == BLACK && sibling->right->color == BLACK)) {
                        sibling->color = RED;
                        node = node->parent;
                    }
                    else {
                        if (sibling->right==nullptr || sibling->right->color == BLACK) {
                            sibling->left->color = BLACK;
                            sibling->color = RED;
                            rotateRight(sibling);
                            sibling = node->parent->right;
                        }
                        sibling->color = node->parent->color;
                        node->parent->color = BLACK;
                        sibling->right->color = BLACK;
                        rotateLeft(node->parent);
                        node = root;
                    }
                }
                else if (node->parent->right==nullptr) {
                    Node<TypeKey, TypeData>* sibling = node->parent->left;

                    if (sibling->color == RED) {
                        sibling->color = BLACK;
                        node->parent->color = RED;
                        rotateRight(node->parent);
                        sibling = node->parent->left;
                    }

                    if ((sibling->left == nullptr && sibling->right == nullptr) || (sibling->left!=nullptr && sibling->right!=nullptr && sibling->left->color == BLACK && sibling->right->color == BLACK)) {
                        sibling->color = RED;
                        node = node->parent;
                    }
                    else {
                        if (sibling->left==nullptr || sibling->left->color == BLACK) {
                            sibling->right->color = BLACK;
                            sibling->color = RED;
                            rotateLeft(sibling);
                            sibling = node->parent->left;
                        }
                        sibling->color = node->parent->color;
                        node->parent->color = BLACK;
                        sibling->left->color = BLACK;
                        rotateRight(node->parent);
                        node = root;
                    }
                }
            }
        }
        node->color = BLACK;
        updateHeights(root);
    }
    void fixInsertion(Node<TypeKey, TypeData>* node) {
        while (node->parent != nullptr && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node<TypeKey, TypeData>* uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateRight(node->parent->parent);
                }
            }
            else {
                Node<TypeKey, TypeData>* uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
        updateHeights(root);
    }

    void insertNode(Node<TypeKey, TypeData>* newNode) {
        Node<TypeKey, TypeData>* parent = nullptr;
        Node<TypeKey, TypeData>* current = root;

        while (current != nullptr) {
            parent = current;
            if (newNode->key < current->key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        newNode->parent = parent;
        if (parent == nullptr) {
            root = newNode;
        }
        else if (newNode->key < parent->key) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }

        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->color = RED;
        fixInsertion(newNode);
    }
    void updateHeight(Node<TypeKey, TypeData>* node) {
        if (node->color == BLACK) {
            node->height = std::max(heightHelper(node->left), heightHelper(node->right)) + 1;
        }
        else {
            node->height = std::max(heightHelper(node->left), heightHelper(node->right));
        }
    }
    int heightHelper(Node<TypeKey, TypeData>* node) {
        return node == nullptr ? 0 : node->height;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(const TypeKey& key, const TypeData& data) {
        Node<TypeKey, TypeData>* newNode=new Node<TypeKey, TypeData>(key, data);
        insertNode(newNode);
    }

    bool updateHeights(Node<TypeKey, TypeData>* node) {
        if (node == nullptr) {
            return true;
        }
        if (updateHeights(node->left) && updateHeights(node->right)) {
            updateHeight(node);
            return true;
        }
    }
    void remove(const TypeKey& key) {
        Node<TypeKey, TypeData>* tmp = root;
        while (tmp->key != key) {
            if (key <= tmp->key) {
                tmp = tmp->left;
            }
            else if (key > tmp->key) {
                tmp = tmp->right;
            }
        }
        Color vcolor = tmp->color;
        if (tmp->left == nullptr && tmp->right == nullptr) {
            Node<TypeKey, TypeData>* parent = tmp->parent;
            if (parent != nullptr && key < parent->key) {
                parent->left = nullptr;
            }
            else if (parent != nullptr) {
                parent->right = nullptr;
            }
            else if (parent == nullptr) {
                root = nullptr;
            }
            if (tmp->color == BLACK) {
                fixRemove(tmp);
            }
            delete tmp;
        }
        else if (tmp->left == nullptr) {
            if (tmp->parent != nullptr && key < tmp->parent->key) {
                tmp->parent->left = tmp->right;
            }
            else if (tmp->parent != nullptr) {
                tmp->parent->right = tmp->right;
            }
            else if (tmp->parent == nullptr) {
                root = tmp->right;
            }
            tmp->right->parent = tmp->parent;
            if (tmp->color == BLACK) {
                fixRemove(tmp->right);
            }
            delete tmp;
        }
        else if (tmp->right == nullptr) {
            if (tmp->parent != nullptr && key < tmp->parent->key) {
                tmp->parent->left = tmp->left;
            }
            else if (tmp->parent != nullptr) {
                tmp->parent->right = tmp->left;
            }
            else if (tmp->parent == nullptr) {
                root = tmp->left;
            }
            tmp->left->parent = tmp->parent;
            if (tmp->color == BLACK) {
                fixRemove(tmp->left);
            }
            delete tmp;
        }
        else {
            TypeKey successork = minHelper(tmp->right)->key;
            TypeData successord = minHelper(tmp->right)->data;
            remove(successork);
            tmp->key = successork;
            tmp->data = successord;
        }
    }
    Node<TypeKey, TypeData>*  minHelper(Node<TypeKey, TypeData>* node) {
        if (node->left == nullptr) {
            return node;
        }
        else {
            return minHelper(node->left);
        }
    }
    void printTree(Node<TypeKey, TypeData>* node, int level) {
        if (node == nullptr) {
            return;
        }
        printTree(node->right, level + 1);
        for (int i = 0; i < level; i++) {
            std::cout << "    ";
        }
        std::cout << node->data << " " << (node->color == RED ? "RED" : "BLACK") << std::endl;
        printTree(node->left, level + 1);
    }
    bool checkconditions(Node<TypeKey, TypeData>* node) {
        if (node == nullptr) {
            return true;
        }
        if (root->color == RED) {
            return false;
        }
        int lheight, rheight;
        if (node->left == nullptr) {
            lheight = 0;
        }
        else {
            lheight = node->left->height;
        }
        if (node->right == nullptr) {
            rheight = 0;
        }
        else {
            rheight = node->right->height;
        }
        if (lheight != rheight) {
            return false;
        }
        if (checkconditions(node->left) && checkconditions(node->right)) {
            return true;
        }
        else {
            return false;
        }
    }
    TypeData& operator[](TypeKey fkey) {
        Node<TypeKey, TypeData>* node = root;
        while (node->key != fkey) {
            if (fkey <= node->key && node->left != NULL) {
                node = node->left;
            }
            else if (fkey > node->key && node->right != NULL) {
                node = node->right;
            }
            else {
                throw "Invalid key";
            }
        }
        return node->data;
    }
    RedBlackTreeIterator<TypeKey, TypeData> find(const TypeKey& key) {
        Node<TypeKey, TypeData>* node = root;
        while (node != nullptr && node->key != key) {
            if (node->key == key) {
                return node;
            }
            else if (key <= node->key) {
                node = node->left;
            }
            else if (key > node->key) {
                node = node->right;
            }
        }
        if (node == nullptr) {
            throw 'FALL';
        }
        return RedBlackTreeIterator<TypeKey, TypeData>(node);
    }
    Node<TypeKey, TypeData>* rootfind() {
        return root;
    }
    RedBlackTreeIterator<TypeKey, TypeData> begin() {
        return RedBlackTreeIterator<TypeKey, TypeData>(minHelper(root));
    }

    RedBlackTreeIterator<TypeKey, TypeData> end() {
        return RedBlackTreeIterator<TypeKey, TypeData>(nullptr);
    }
    void display() {
        printTree(root, 0);
    }
};
