#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool lthread, rthread;
};

Node* createNode(int value) {
    Node* temp = new Node;
    temp->data = value;
    temp->left = NULL;
    temp->right = NULL;
    temp->lthread = true;
    temp->rthread = true;
    return temp;
}

Node* leftMost(Node* ptr) {
    if (ptr == NULL) return NULL;
    while (!ptr->lthread)
        ptr = ptr->left;
    return ptr;
}

// Insert a value into the threaded BST
Node* insert(Node* root, int key) {
    if (root == NULL) return createNode(key);

    Node* ptr = root;
    while (true) {
        if (key == ptr->data) {
            cout << "Duplicate value, not inserted.\n";
            return root;
        }
        if (key < ptr->data) {
            if (ptr->lthread) {
                Node* n = createNode(key);
                n->left = ptr->left;
                n->right = ptr;
                ptr->left = n;
                ptr->lthread = false;
                break;
            }
            ptr = ptr->left;
        } else {
            if (ptr->rthread) {
                Node* n = createNode(key);
                n->right = ptr->right;
                n->left = ptr;
                ptr->right = n;
                ptr->rthread = false;
                break;
            }
            ptr = ptr->right;
        }
    }
    return root;
}

// Find the node holding 'key' (NULL if absent)
Node* search(Node* root, int key) {
    Node* ptr = root;
    while (ptr != NULL) {
        if (key == ptr->data) return ptr;
        if (key < ptr->data) {
            if (ptr->lthread) return NULL;
            ptr = ptr->left;
        } else {
            if (ptr->rthread) return NULL;
            ptr = ptr->right;
        }
    }
    return NULL;
}

// Inorder successor using thread information
Node* inorderSuccessor(Node* ptr) {
    if (ptr == NULL)
        return NULL;

    // Case 1: right link is a thread -> it points straight to the successor
    if (ptr->rthread)
        return ptr->right;

    // Case 2: right link is a real child -> successor is the
    // leftmost node of the right subtree
    return leftMost(ptr->right);
}

void inorder(Node* root) {
    Node* cur = leftMost(root);
    while (cur != NULL) {
        cout << cur->data << " ";
        cur = inorderSuccessor(cur);
    }
    cout << endl;
}

Node* destroyTree(Node* root) {
    Node* cur = leftMost(root);
    while (cur != NULL) {
        Node* next = inorderSuccessor(cur);
        delete cur;
        cur = next;
    }
    return NULL;
}

int main() {
    Node* root = NULL;
    int n, value;

    cout << "How many nodes to insert? ";
    cin >> n;
    cout << "Enter " << n << " values: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        root = insert(root, value);
    }

    if (root == NULL) {
        cout << "Tree is empty.\n";
        return 0;
    }

    cout << "Inorder traversal: ";
    inorder(root);

    char again;
    do {
        cout << "\nEnter the node whose inorder successor you want: ";
        cin >> value;

        Node* target = search(root, value);
        if (target == NULL) {
            cout << "Node " << value << " not found in the tree.\n";
        } else {
            Node* succ = inorderSuccessor(target);
            if (succ == NULL) {
                cout << "Node " << value << " is the last node in inorder; it has no successor.\n";
            } else {
                cout << "Inorder successor of " << value << " is " << succ->data << endl;
                if (target->rthread)
                    cout << "Found via: right THREAD\n";
                else
                    cout << "Found via: leftmost node of RIGHT SUBTREE\n";
            }
        }

        cout << "Find another? (y/n): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');

    root = destroyTree(root);
    return 0;
}
