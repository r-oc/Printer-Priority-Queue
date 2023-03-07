#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct node
{
	void* dataPtr;
	struct node* next;
} NODE;

typedef struct list
{
	NODE* head;
	int count;
} LIST;

typedef struct document
{
	int docID;
	int priority;
	int pages;
	int cycles;
} DOCUMENT;

// FUNCTION DECLARATION
LIST* createLinkedList(void);
DOCUMENT* createDocument();
void printDocument(DOCUMENT * doc);
void insertNode(NODE* node, LIST* list);
void printLinkedList(LIST* list);

// CONST VARIABLES
const int MAX_PAGES = 10;

int main() {
    
    printf("Printer Priority Queue\n");
    LIST * list = createLinkedList();
    
    srand(time(NULL));   // Initialization, should only be called once.
    int c = 1;
    
    for(int i = 0; i < 100; i++) {
        int r = rand() % 10;
        
        // Doing the action when r == 1 out of 10 (10% chance we do this action)
        if(r == 1) {
            
            // Create document and allocate a document number depending on when it is created.
            DOCUMENT* doc = createDocument();
            doc->docID = c;
            //printDocument(doc); //[testing]
            
            // Increment document id counter whenever we create a new document.
            c++;
            
            // Create new node
            NODE* node = (NODE*)malloc(sizeof(NODE));
            node->dataPtr = doc;
			
            // Insert it in order
            insertNode(node, list);
        }
        
    }
    /*TESTING TESTING
    NODE* testNode1 = (NODE*)malloc(sizeof(NODE));
    DOCUMENT* testDoc1 = (DOCUMENT*)malloc(sizeof(DOCUMENT));
    testDoc1->priority = 3;
    testDoc1->docID = 1;
    testDoc1->pages = 2;
    testDoc1->cycles = 0;
    testNode1->dataPtr = testDoc1;
    list->head = testNode1;
    
    insertNode(testNode1, list);
    
    NODE* testNode2 = (NODE*)malloc(sizeof(NODE));
    DOCUMENT* testDoc2 = (DOCUMENT*)malloc(sizeof(DOCUMENT));
    testDoc2->priority = 3;
    testDoc2->docID = 2;
    testDoc2->pages = 22;
    testDoc2->cycles = 0;
    testNode2->dataPtr = testDoc2;
    
    insertNode(testNode2, list);

    NODE* testNode3 = (NODE*)malloc(sizeof(NODE));
    DOCUMENT* testDoc3 = (DOCUMENT*)malloc(sizeof(DOCUMENT));
    testDoc3->priority = 2;
    testDoc3->docID = 3;
    testDoc3->pages = 3;
    testDoc3->cycles = 0;
    testNode3->dataPtr = testDoc3;
    
    insertNode(testNode3, list);
    
    NODE* testNode4 = (NODE*)malloc(sizeof(NODE));
    DOCUMENT* testDoc4 = (DOCUMENT*)malloc(sizeof(DOCUMENT));
    testDoc4->priority = 2;
    testDoc4->docID = 4;
    testDoc4->pages = 3;
    testDoc4->cycles = 0;
    testNode4->dataPtr = testDoc4;
    
    insertNode(testNode4, list);
*/
    printLinkedList(list);

    printf("End of program\n");
    
    return 0;
}

DOCUMENT* createDocument() {

    int r1 = rand() % 10;
    int r2 = rand() % 10;
    int rand_pages = rand() % MAX_PAGES + 1;
    DOCUMENT * newDoc = (DOCUMENT*)malloc(sizeof(DOCUMENT));
    

    if(r2 == 1) {
        newDoc->docID = 1;
        newDoc->priority = 1; // high
        newDoc->pages = rand_pages;
        newDoc->cycles = 0;            
    } else if(r2 >= 2 && r2 <= 8) {
        newDoc->docID = 1;
        newDoc->priority = 2; // average
        newDoc->pages = rand_pages;
        newDoc->cycles = 0;          
    } else {
        newDoc->docID = 1;
        newDoc->priority = 3; // low
        newDoc->pages = rand_pages;
        newDoc->cycles = 0;          
    }
    
    return newDoc;

}

void printDocument(DOCUMENT * doc) {
    printf("\nCurrent Print Queue : DocNum %2d  NumOfPage %2d  PriorityLevel %d  NumOfCycles %d\n", doc->docID,doc->pages, doc->priority, doc->cycles);
}

void printLinkedList(LIST* list) {
    
    NODE* currNode = list->head;
    printf("Did we get here before core dump, list size is %d\n", list->count);
    
    
    while(currNode != NULL) {
        
        printf("\nCurrent Print Queue : DocNum %2d  NumOfPage %2d  PriorityLevel %d  NumOfCycles %d\n", ((DOCUMENT*)currNode->dataPtr)->docID, ((DOCUMENT*)currNode->dataPtr)->pages, ((DOCUMENT*)currNode->dataPtr)->priority, ((DOCUMENT*)currNode->dataPtr)->cycles);
        
        currNode = currNode->next;
    }
    
}


LIST* createLinkedList(void) 
{
	LIST* list;
	list = (LIST*)malloc(sizeof(LIST));
	
	list->head = NULL;
	list->count = 0;
	
	return list;
}

int compareTo(DOCUMENT * doc1, DOCUMENT * doc2)
{
    //if doc1 > doc2 then return 1, else -1, return 0 if equal
    int priority1 = doc1->priority;
    int priority2 = doc2->priority;
    int page1 = doc1->pages;
    int page2 = doc2->pages;
    
    if (priority1 > priority2)
        return 1;
    else if (priority1 < priority2)
        return -1;
    else { //when they, mean priority 1 and 2 are equal
        if(page1 > page2) {
            return 1;
        } else if(page1 < page2) {
            return -1;
        } else return 0;
        
    }
}

void insertNode(NODE* node, LIST* list) {

    // printf("\n----- Start of insertNode -----\n");

    // If the list is empty, set list->head to the given node. Set next to null and increase count.
    if(list->head == NULL) {
        list->head = node;
        node->next = NULL;
        (list->count)++;
        return;
    }
    
    NODE* temp = list->head;    // Save the entire list in temp. Will be overwritten later if needed.
    
    // If given node is less than the head node it is a special case where we set the head to given node.
    // Save the entire list in temp (head node). Set list head to given node, and node->next to temp, which is the rest of the list. Also increase count+1 because we have added a node. However, we cannot blindly set node->next to null because it could store an entire list we don't want to lose.
    if(compareTo(node->dataPtr, list->head->dataPtr) == -1) {
        list->head = node;  // Set new head to node.
        node->next = temp;  // Set next to temp (the rest of the list), to preserve it.
        (list->count)++;    // Increase count because we have added a node.
        return;             // Return since we have added the node and do not have to continue.
    }
    
    // Now we have processed the EMPTY LIST and HEAD NODE. 
    NODE* currNode = list->head->next;
    NODE* prevNode = list->head;
    // Rest of nodes except head
    while(currNode != NULL) {
        //printf("\nCURRENT NODE DOCID: %d\n", ((DOCUMENT*)currNode->dataPtr)->docID);
        
        // If given is less than current node, insert to the left of current node.
        if(compareTo(node->dataPtr, currNode->dataPtr) == -1) {
            prevNode->next = node;
            node->next = currNode;
            (list->count)++;
            return;
        }
        
        // If given node is equal to current node, we place to the right of current node.
        if(compareTo(node->dataPtr, currNode->dataPtr) == 0) {
            // Overwrite temp with currNode->next. Insert new node to the right (next) of currentNode. Re-insert the rest of the list to the right (next) of new node.
            temp = currNode->next;
            currNode->next = node;
            node->next = temp;
            (list->count)++;
            return;
        }
        
        // Cycle through the nodes, while preserving the previous node.
        prevNode = currNode;
        currNode = currNode->next;
    }
    
    // Add to end
    // Now if we reach this line of code (function doesn't return), then we need to just add it to the end of the list. 
    // At this point, prevNode will be equal to the LAST actual node in the list, while currNode will be equal to NULL, the pointer after the last node in the list, since the loop continues until currNode == NULL.
    
    prevNode->next = node;
    node->next = NULL;
    (list->count)++;
    
    printf("\n----- End of insertNode -----\n");
    
}







