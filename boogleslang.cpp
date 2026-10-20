#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

struct trieNode {
    char desc[101];
    trieNode *children[256];
    bool EndOfWord;
};

int totalWords = 0;

trieNode *createNode() {
    return (trieNode *)calloc(1, sizeof(trieNode));
}

bool validWord(char *word) {
    return strlen(word) > 1 && strchr(word, ' ') == NULL;
}

bool validDesc(char *desc) {
    char temp[101];
    strcpy(temp, desc);
    int count = 0;
    for (char *token = strtok(temp, " "); token != NULL; token = strtok(NULL, " "))
        count++;
    return count > 1;
}

void inputWord(const char *question, char *word) {
    do {
        printf("%s", question);
        fgets(word, 100, stdin);
        word[strcspn(word, "\n")] = '\0';
    } while (!validWord(word));
}

trieNode *findNode(trieNode *root, char *word) {
    trieNode *curr = root;
    for (int i = 0; word[i] && curr; i++)
        curr = curr->children[(unsigned char)word[i]];
    return curr;
}

void push(trieNode *root, char *word, char *desc) {
    trieNode *curr = root;
    for (int i = 0; word[i]; i++) {
        int idx = (unsigned char)word[i];
        if (curr->children[idx] == NULL) curr->children[idx] = createNode();
        curr = curr->children[idx];
    }

    strcpy(curr->desc, desc);
    if (curr->EndOfWord) {
        printf("\nSuccessfully updated a slang word.\n");
    } else {
        printf("\nSuccessfully released new slang word.\n");
        curr->EndOfWord = true;
        totalWords++;
    }
}

void viewTree(trieNode *node, char *prefix, int depth, int *count) {
    if (node->EndOfWord) {
        prefix[depth] = '\0';
        printf("%d. %s\n", (*count)++, prefix);
    }
    for (int i = 0; i < 256; i++) {
        if (node->children[i]) {
            prefix[depth] = i;
            viewTree(node->children[i], prefix, depth + 1, count);
        }
    }
}

void printTitle() {
    printf("\x1b[96m");
    printf("  ____   ___   ___   ____ _     _____  \n");
    printf(" | __ ) / _ \\ / _ \\ / ___| |   | ____|\n");
    printf(" |  _ \\| | | | | | | |  _| |   |  _|  \n");
    printf(" | |_) | |_| | |_| | |_| | |___| |___  \n");
    printf(" |____/ \\___/ \\___/ \\____|_____|_____|\n");
    printf("\x1b[0m\n");
}

int main() {
    trieNode *root = createNode();
    int opt;
    char word[101], desc[101], temp[101];

    while (1) {
        system(CLEAR);
        printTitle();
        puts("1. Release a new slang word");
        puts("2. Search a slang word");
        puts("3. View all slang words starting with a certain prefix word");
        puts("4. View all slang words");
        puts("5. Exit");
        printf(">> ");
        scanf("%d", &opt);
        getchar();

        if (opt == 1) {
            inputWord("Input a new slang word [Must be more than 1 characters and contains no space]: ", word);
            do {
                printf("Input a new slang word description [Must be more than 2 words]: ");
                fgets(desc, 100, stdin);
                desc[strcspn(desc, "\n")] = '\0';
            } while (!validDesc(desc));
            push(root, word, desc);
        }
        else if (opt == 2) {
            inputWord("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ", word);
            trieNode *found = findNode(root, word);
            if (found && found->EndOfWord) {
                printf("\nSlang word  : %s\n", word);
                printf("Description : %s\n", found->desc);
            } else {
                printf("\nThere is no word \"%s\" in the dictionary.\n", word);
            }
        }
        else if (opt == 3) {
            do {
                printf("Input a prefix to be searched: ");
                fgets(word, 100, stdin);
                word[strcspn(word, "\n")] = '\0';
            } while (strlen(word) == 0);
            trieNode *prefixNode = findNode(root, word);
            if (prefixNode) {
                printf("\nWords starts with \"%s\":\n", word);
                strcpy(temp, word);
                int count = 1;
                viewTree(prefixNode, temp, strlen(word), &count);
            } else {
                printf("\nThere is no prefix \"%s\" in the dictionary.\n", word);
            }
        }
        else if (opt == 4) {
            if (totalWords == 0) {
                printf("\nThere is no slang word yet in the dictionary.\n");
            } else {
                printf("\nList of all slang words in the dictionary:\n");
                int count = 1;
                viewTree(root, temp, 0, &count);
            }
        }
        else if (opt == 5) {
            printf("\nThank you... Have a nice day :)\n");
            break;
        }
        else {
            printf("Invalid In.\n");
        }

        printf("\nPress enter to continue...");
        getchar();
    }
    return 0;
}
