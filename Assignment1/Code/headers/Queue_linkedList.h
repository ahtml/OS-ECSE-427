#ifndef QUEUE_LINKEDLIST_H_   /* Include guard */
#define QUEUE_LINKEDLIST_H_

struct Node;
//struct Node** front;
//struct Node** rear;

void enqueue(char* info, int* index, struct Node** front, struct Node** rear);
void dequeue(struct Node** front, struct Node** rear);
char* getItem(struct Node** front, int index);
void printList(struct Node** front);
int size(struct Node** front);

#endif // QUEUE_LINKEDLIST_H_