//SCT221-0378/2022 - NEEMA MUTANU
//SCT221-0224/2022 - CHRISTINE WAMBUI 

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

int height(Node* node) {
    if (node == NULL)
        return -1;
    else {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}

Node* minNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = minNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void printLevelAndHeight(Node* root, int data, int level) {
    if (root == NULL)
        return;

    if (root->data == data) {
        printf("Node %d is at level %d and its height is %d.\n", data, level, height(root));
    } else if (data < root->data) {
        printLevelAndHeight(root->left, data, level + 1);
    } else {
        printLevelAndHeight(root->right, data, level + 1);
    }
}

int main() {
    Node* root = NULL;
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < arrSize; i++) {
        root = insert(root, arr[i]);
    }

    printf("Height of the BST: %d\n", height(root));

    root = deleteNode(root, 20);
    printLevelAndHeight(root, 35, 1);

    return 0;
}

