#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left, *right;
};

// Function to create a new BST node
struct Node* newNode(int key) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a node in the BST
struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

// Function to find the minimum value node
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Function to calculate the height of the BST
int height(struct Node* node) {
    if (node == NULL)
        return 0;
    else {
        int lHeight = height(node->left);
        int rHeight = height(node->right);
        return (lHeight > rHeight ? lHeight : rHeight) + 1;
    }
}

// Function to print level of a node
int getLevelUtil(struct Node *node, int key, int level) {
    if (node == NULL)
        return 0;

    if (node->key == key)
        return level;

    int downlevel = getLevelUtil(node->left, key, level+1);
    if (downlevel != 0)
        return downlevel;

    downlevel = getLevelUtil(node->right, key, level+1);
    return downlevel;
}

int getLevel(struct Node *node, int key) {
    return getLevelUtil(node, key, 1);
}

// Driver program to test above functions
int main() {
    struct Node* root = NULL;
    int array[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(array)/sizeof(array[0]);
    int keyToDelete;

    for (int i = 0; i < n; i++)
        root = insert(root, array[i]);

    // Prompt user for the node key to delete
    printf("Enter the node key you want to delete: ");
    scanf("%d", &keyToDelete);

    root = deleteNode(root, keyToDelete);

    // Print the height of the BST
    printf("Height of the BST: %d\n", height(root));

    // Print the level and height of a node
    int node_key; // Variable to store the node key for which to find level and height
    printf("Enter the node key to find its level and height: ");
    scanf("%d", &node_key);

    printf("Level of node %d is %d\n", node_key, getLevel(root, node_key));
    printf("Height of the BST from node %d is %d\n", node_key, height(root));

    return 0;
}
