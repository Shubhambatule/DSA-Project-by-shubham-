
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
    if (ptr == NULL)
        return NULL;

    while (!ptr->lthread)
        ptr = ptr->left;

    return ptr;
}

Node* insert(Node* root, int key) {
    if (root == NULL)
        return createNode(key);

    Node* ptr = root;

    while (true) {
        if (key == ptr->data) {
            cout << "Duplicate value " << key
                 << ", not inserted.\n";
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
        }
        else {
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

Node* search(Node* root, int key) {
    Node* ptr = root;

    while (ptr != NULL) {
        if (key == ptr->data)
            return ptr;

        if (key < ptr->data) {
            if (ptr->lthread)
                return NULL;

            ptr = ptr->left;
        }
        else {
            if (ptr->rthread)
                return NULL;

            ptr = ptr->right;
        }
    }

    return NULL;
}

Node* inorderSuccessor(Node* ptr) {
    if (ptr == NULL)
        return NULL;

    if (ptr->rthread)
        return ptr->right;

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

void processQuery(Node* root, int value) {
    Node* target = search(root, value);

    if (target == NULL) {
        cout << "Node " << value
             << ": NOT FOUND in the tree.\n";
        return;
    }

    Node* succ = inorderSuccessor(target);

    if (succ == NULL) {
        cout << "Node " << value
             << ": NO inorder successor "
             << "(last node in inorder).\n";
        return;
    }

    cout << "Node " << value
         << ": successor = " << succ->data
         << " [reached via ";

    if (target->rthread)
        cout << "THREAD";
    else
        cout << "CHILD LINK "
             << "(leftmost node of right subtree)";

    cout << "]\n";
}

int main() {
    Node* root = NULL;
    int n, value;

    cout << "How many nodes to insert? ";

    if (!(cin >> n) || n <= 0) {
        cout << "Invalid number of nodes.\n";
        return 0;
    }

    cout << "Enter " << n << " values: ";

    for (int i = 0; i < n; i++) {
        if (!(cin >> value)) {
            cout << "Invalid input.\n";
            root = destroyTree(root);
            return 0;
        }

        root = insert(root, value);
    }

    cout << "Inorder traversal: ";
    inorder(root);

    int q;

    cout << "\nHow many nodes do you want "
         << "to find successors for? ";

    if (!(cin >> q) || q <= 0) {
        cout << "Invalid number of queries.\n";
        root = destroyTree(root);
        return 0;
    }

    int queries[1000];

    if (q > 1000) {
        cout << "Maximum 1000 queries allowed.\n";
        root = destroyTree(root);
        return 0;
    }

    cout << "Enter " << q << " node values: ";

    for (int i = 0; i < q; i++) {
        if (!(cin >> queries[i])) {
            cout << "Invalid input.\n";
            root = destroyTree(root);
            return 0;
        }
    }

    cout << "\n--- Results ---\n";

    for (int i = 0; i < q; i++)
        processQuery(root, queries[i]);

    root = destroyTree(root);

    return 0;
}
