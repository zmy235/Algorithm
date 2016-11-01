//*******************************************
//ListMergeSort.cpp   2014/6/1 by Adaq
//@brief: 本文件为MergeSort Of List的C++实现。
//*******************************************
#include <stdio.h>
#include <stdlib.h>

class NODE
{
public:
    int data;
    node* next;
};

/*function prototype */
node* SortedMerge( node* a,  node* b);
void FrontBackSplit( node* source,  node** frontRef,  node** backRef);

/*sorts the linked list by changing next pointers(not data) */
void MergeSort( node** headRef)
{
    node* head = *headRef;
    node* a;
    node* b;

    /*base case-- length 0 or 1 */
    if((head == NULL) || (head->next == NULL))
    {
        return;
    }

    /*Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /*Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}

node* SortedMerge( node* a,  node* b)
{
    node* result = NULL;

    /* Base cases */
    if(a == NULL)
        return (b);
    else if(b == NULL)
        return (a);

    /* Pick either a or b recur */
    if(a->data <= b->data)
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
    and return the two lists using the references paramet
    If the length is odd, the extra node shold go in the front l
    Uses the fast/slow pointer strat  */
void FrontBackSplit( node* source,  node** frontRef,  node** backRef)
{
    node* fast;
    node* slow;

    if(source == NULL || source->next == NULL)
    {
        *frontRef = source;
        *backRef = NULL;
    }
    else
    {
        slow = source;
        fast = source->next;

        /* Advance 'fast' two nodes, and advance 'slow' one node */
        while(fast != NULL)
        {
            fast = fast->next;
            if( fast != NULL )
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}

/*Function to print nodes in a given linked list*/
void printList( node* node)
{
    while( node != NULL )
    {
        printf("%d  ", node->data);
        node = node->next;
    }
}

/* Function to insert a node at the begining of the linked list*/
void push( node** head_ref, int new_data)
{
    /*allocate node*/
    node* new_node = ( node*)malloc(sizeof( node));

    /*put in the data*/
    new_node->data = new_data;

    /*link the old list off the new node*/
    new_node->next = (*head_ref);

    /*move the head to point to the new node*/
    (*head_ref) = new_node;
}

/* Drier program to test above functions*/
int main()
{
    /* Start with the empty list */
    node* res = NULL;
    node* a = NULL;

    /* Let us create a unsorted linked lists to test the functions
       Created lists shall be a: 2->3->20->5->10->15 */
    push(&a, 15);
    push(&a, 10);
    push(&a, 5);
    push(&a, 20);
    push(&a, 3);
    push(&a, 2);

    /* Sort the above created Linked List */
    MergeSort(&a);

    printf("\n Sorted Linked List is: \n");
    printList(a);

    return 0;
}

