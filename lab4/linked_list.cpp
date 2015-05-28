#include <iostream>
#include <string> 

#define L1 true
#define L2 false

using namespace std;

struct Node {
    int key;
    string value;
    Node* next;
}; 

// Pre-condition: The head of a linked list is provided and a key-value 
// pair to insert.
// Post-condition: The linked list now contains that element at the front.
void insert( Node*& head, int key, string value) {

    Node * temp;
    temp = new Node;
    temp->key = key;
    temp->value = value;

    temp->next = head;
    head = temp;
    
}

// Pre-condition: A linked list is provided.
// Post-condition: The linked list is printed to standard output.
void print( Node* head ) {
    Node* temp = head;
    while( temp != NULL ) {
	cout << "key: " << temp->key << " value: " << temp->value << endl;
        temp = temp->next;
    }
	cout<<endl;
}

// Pre-condition: The head of a linked list is provided.
// Post-condition: The last element of that linked list has been removed.
void delete_last_element( Node*& head )
{    
    if(head == NULL)
        return;
    else if(head->next == NULL) {
		cout << "Deleted head element with key: " << head->key 
				<< " and string: " << head->value << endl;
        delete head;
        head = NULL;
    } else {
        Node * newLast = head;
        Node * last = head->next;
        
        while(last->next != NULL) {
            newLast = last;
            last = last->next;
        }
		cout << "Deleted last element with key: " << last->key 
				<< " and string: " << last->value << endl;
        delete last;
        newLast->next = NULL;
    }
}


// Pre-condition: The head of a linked list is provided, and a key-value
// pair to insert after the indicated key.
// Post-condition: The linked list now contains that element.
void insert_after( Node*& head, int key, int newKey, string value )
{
    bool keyExists = false;
    
    Node* temp = head;
        
    while(temp != NULL)
        if(temp->key == key) {
            keyExists = true;
            break;
        } else 
            temp = temp->next;
        
    if(keyExists == true) {
        Node* insert = new Node;
        insert->key = newKey;
        insert->value = value;
        
        if(temp->next != NULL) 
            insert->next = temp->next;
        temp->next = insert;
    } else
        cout << "Error in insertion... Node with key: " << key
				<< " does not exist in specified list" << endl;
}


// Pre-condition: Two linked lists are provided.
// Post-condition: A linked list is returned that is the result of
// interleaving the elements from each list provided (e.g. {1, 2, 3} &
// { 4, 5, 6} would return {1, 4, 2, 5, 3, 6}
Node* interleave( Node*& list1, Node*& list2 )
{
	//please write your own code here to replace "return NULL" below
	Node* temp = NULL, *listFinal = NULL, *head1 = NULL, *head2 = NULL;
	head1 = list1;
	head2 = list2;
	bool whichList = L1;
	int currentKey = 0;
	string curretVal = "lol";
	
    while( list1 != NULL || list2 != NULL ) {
		if (whichList == L1) {
			currentKey = list1->key;
			curretVal = list1->value;
			list1 = list1->next;
			if (list2 != NULL) {
				whichList = L2;
			}
		} else {
			currentKey = list2->key;
			curretVal = list2->value;
			list2 = list2->next;
			if (list1 != NULL) {
				whichList = L1;
			}
		}
		insert(temp, currentKey, curretVal);
    }
	
    while( temp != NULL) {
		currentKey = temp->key;
		curretVal = temp->value;
		temp = temp->next;
		insert(listFinal, currentKey, curretVal);
    }
	
	list1 = head1;
	list2 = head2;
		
	return listFinal;
}

int main() {

    Node * list1 = NULL;
    Node * list2 = NULL;
	Node * list3 = NULL;
	Node * list4 = NULL;

    insert( list1, 1, "one");
    insert( list1, 2, "two");

    cout << "<1> Linked List 1..." << endl;
    print( list1 );

    insert( list2, 10, "ten");
    insert( list2, 9, "nine");
    insert( list2, 8, "eight");
    insert( list2, 7, "seven");
    insert( list2, 6, "six");

    cout << "<2> Linked List 2..." << endl;
    print( list2 );

	delete_last_element( list1 );
    cout << "<3> Linked List 1..." << endl;
	print( list1 );

	delete_last_element( list1 );
    cout << "<4> Linked List 1..." << endl;
	print( list1 );

	delete_last_element( list1 );
    cout << "<5> Linked List 1..." << endl;
	print( list1 );

	insert(list1, 11, "eleven");
	insert_after(list1, 11, 12, "twelve");
    cout << "<6> Linked List 1..." << endl;
	print( list1 );


	insert_after(list1, 13, 14, "fourteen");
    cout << "<7> Linked List 1..." << endl;
	print( list1 );

	list4 = interleave(list1, list2);
    cout << "<8> Linked List 4..." << endl;
	print( list4 );

	list4 = interleave(list1, list3);
    cout << "<9> Linked List 4..." << endl;
	print( list4 );

	list4 = interleave(list3, list3);
    cout << "<10> Linked List 4..." << endl;
	print( list4 );
	
	insert_after(list2, 8, 30, "thirty");
    cout << "<11> Linked List 2..." << endl;
	print( list2 );

    return 0;
}
