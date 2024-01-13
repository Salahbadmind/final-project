
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char letter;
    struct TreeNode* children[26]; 
    int isEndOfWord;
} TreeNode;


TreeNode* createNode(char letter) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->letter = letter;
    node->isEndOfWord = 0;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}


void insertWord(TreeNode* root, char* word) {
    TreeNode* current = root;
    int length = strlen(word);

    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a';

        if (!current->children[index]) {
            current->children[index] = createNode(word[i]);
        }

        current = current->children[index];
    }

    current->isEndOfWord = 1;
}


void searchWord(TreeNode* root, char* letters, int n) {
    TreeNode* current = root;

    for (int i = 0; i < n; i++) {
        int index = letters[i] - 'a';

        if (!current->children[index]) {
            printf("No words found with the given letters.\n");
            return;
        }

        current = current->children[index];
    }

    printf("Found a word: %s\n", letters);
}


void deleteTree(TreeNode* root) {
    if (!root) return;

    for (int i = 0; i < 26; i++) {
        if (root->children[i]) {
            deleteTree(root->children[i]);
        }
    }

    free(root);
}

int main() {
    TreeNode* dictionaryRoot = createNode('\0');

  
    insertWord(dictionaryRoot, "apple");
    insertWord(dictionaryRoot, "banana");
    insertWord(dictionaryRoot, "orange");
  

   
    char letters[] = "aoperng";
    int length = strlen(letters);

    searchWord(dictionaryRoot, letters, length);

 
    deleteTree(dictionaryRoot);

    return 0;
}
