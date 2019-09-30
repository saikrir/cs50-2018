#include <stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct Node
{
    char name[50];
    struct Node *next;
} Node;


void printLinkedlist(Node *begin) {
    printf("Printing List \n");
    for(Node *n = begin; n!=NULL ; n= n-> next) {
        printf("%s \n", n-> name);
    }
}

void printMenu() {
    printf("\n\n********** List Options ************** \n");
    printf("1. Insert a Value \n");
    printf("2. Print values \n");
    printf("3. Search a Value \n");
    printf("4. Delete a Value \n");
    printf("5. Quit \n");
    //printf("Enter your choice : ");
}

Node* findLastNode(Node *root) 
{
    if(root != NULL )
    {
        Node *lastNode = root;

        while( lastNode -> next != NULL) {
            lastNode =  lastNode ->next;    
        }

        return lastNode;
    }
    else
    {
        return root;
    }
}

int main(int argc, char const *argv[])
{
    int choice = 0;

    Node *root = NULL;

    do {
        printMenu();
        choice = get_int("Enter your choice : ");

        switch (choice)
        {
        case 1:
            {
                char *name  = get_string("Name : ");
                if(root == NULL) {
                    root = malloc(sizeof(Node));
                    strcpy(root->name, name);
                    root->next = NULL;
                    printf("More 1 %s ", root->name);
                }
                else {
                    Node *n = malloc(sizeof(Node));  
                    strcpy(n->name, name);
                    n->next = NULL;
                    Node *lastNode = findLastNode(root);
                    lastNode -> next = n;
                }
            }
            break;
        case 2:
            {
                if(root != NULL ) {
                    printLinkedlist(root);
                }
                else {
                    printf("List is Empty \n");
                }
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            printf("Thank you! \n");
            break;
        default:
            break;
        }
    }
    while(choice != 5);

    
    if(root!=NULL) {
        free(root);
    }

    return 0;
}
