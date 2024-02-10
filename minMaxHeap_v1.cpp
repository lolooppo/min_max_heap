#include<bits/stdc++.h>
using namespace std;


/***************************************************************************************************************
Author : Alaa Ibrahim Mohamed.

Objective : building a new data structure which provides these methods : minimum -> {o(1)} , maximum -> {o(1)}.

Idea : the idea is to use a minHeap , maxHeap and a doubly linked list...
       the min and max heaps will hold a pointer to pointer node(the doubly linked list node).

****************************************************************************************************************/



struct node{
    int data{-1} , minHeapIdx{-1} , maxHeapIdx{-1};
    node* prev{nullptr} ,* next{nullptr};



    //constructor
    node(int data){
        this->data = data;
    }
};




struct doublyLinkedList{
    node* head{nullptr};



    void pop(node* trgt){
        node* prev_node = trgt->prev;
        node* next_node = trgt->next;

        if(prev_node){
            prev_node->next = next_node;
        }

        if(next_node){
            next_node->prev = prev_node;
        }

        if(trgt == head)        //delete the head case , so update it first
            head = head->next;

        delete trgt;
        trgt = nullptr;

    }



    void push(node* trgt){

        if(!head){          //the list is empty
            head = trgt;
            return;
        }

        head->prev = trgt;
        trgt->next = head;
        head = trgt;
    }



    void print(){
        node* dummy = head;

        while(dummy){
            cout<<dummy->data<<" ";
            dummy = dummy->next;
        }

        cout<<"\n";
    }
};





struct minHeap{
    int capacity{-1} , current_idx{-1};
    node** minHeapArray{nullptr};



    minHeap(int capacity){
        this->capacity = capacity;
        minHeapArray = new node* [capacity];
    }




    /***********************************************************
    methods to get the parent , leftChild and rightChild indexes
    ************************************************************/
    int parent(int idx){
        idx--;
        return idx < 0 ? -1 : idx / 2 ;
    }
    int left(int idx){
        idx *= 2;
        idx++;
        return idx > current_idx ? -1 : idx ;
    }
    int right(int idx){
        idx *= 2;
        idx += 2;
        return idx > current_idx ? -1 : idx ;
    }




    /*
    fix the tree up
    */
    void heapifyUp(int idx){
        int parent_idx = parent(idx);

        if(parent_idx == -1)        //the root case
            return;

        if(minHeapArray[parent_idx]->data > minHeapArray[idx]->data){
            swap(minHeapArray[parent_idx] , minHeapArray[idx]);
            swap(minHeapArray[parent_idx]->minHeapIdx , minHeapArray[idx]->minHeapIdx);   //update the indexes

            heapifyUp(parent_idx);
        }
    }




    /*
        fix the tree down
    */
    void heapifyDown(int idx){
        int left_idx = left(idx) , right_idx = right(idx);

        if(left_idx == -1)      //leaf node case := which has no childs
            return;

        if(right_idx !=-1 and minHeapArray[left_idx]->data < minHeapArray[right_idx]->data){
            swap(minHeapArray[left_idx] , minHeapArray[right_idx]);
            swap(minHeapArray[left_idx]->minHeapIdx , minHeapArray[right_idx]->minHeapIdx); //update indexes
        }
        if(minHeapArray[idx]->data > minHeapArray[left_idx]->data){
            swap(minHeapArray[idx] , minHeapArray[left_idx]);
            swap(minHeapArray[idx]->minHeapIdx , minHeapArray[left_idx]->minHeapIdx);       //update indexes

            heapifyDown(left_idx);
        }
    }




    void push(node* trgt){
        assert(!full());

        minHeapArray[++current_idx] = trgt;
        minHeapArray[current_idx]->minHeapIdx = current_idx;

        heapifyUp(current_idx);
    }




    node* pop(){
        assert(!empty());

        swap(minHeapArray[current_idx] , minHeapArray[0]);
        swap(minHeapArray[current_idx]->minHeapIdx , minHeapArray[0]->minHeapIdx);

        current_idx--;
        heapifyDown(0);

        return minHeapArray[current_idx + 1];               //will be used to delete from the doubly linked list
    }




    void pop_idx(int idx){
        assert(!empty() and idx <= current_idx);

        swap(minHeapArray[idx] , minHeapArray[0]);
        swap(minHeapArray[idx]->minHeapIdx , minHeapArray[0]->minHeapIdx);
        swap(minHeapArray[current_idx] , minHeapArray[0]);
        swap(minHeapArray[current_idx]->minHeapIdx , minHeapArray[0]->minHeapIdx);

        current_idx--;

        heapifyDown(0);
    }



    int top(){
        assert(!empty());

        return minHeapArray[0]->data;
    }



    bool empty(){
        return current_idx == -1;
    }




    bool full(){
        return (current_idx + 1) == capacity;
    }
};






/************************************************************
same as the min heap(code above) ,but the comparisons differs.
*************************************************************/
struct maxHeap{
    int capacity{-1} , current_idx{-1};
    node** maxHeapArray{nullptr};




    maxHeap(int capacity){
        this->capacity = capacity;
        maxHeapArray = new node* [capacity];
    }




    int parent(int idx){
        idx--;

        return idx < 0 ? -1 : idx / 2 ;
    }
    int left(int idx){
        idx *= 2;
        idx++;

        return idx > current_idx ? -1 : idx ;
    }
    int right(int idx){
        idx *= 2;
        idx += 2;

        return idx > current_idx ? -1 : idx ;
    }




    void heapifyUp(int idx){
        int parent_idx = parent(idx);
        if(parent_idx == -1)                //the root case
            return;

        if(maxHeapArray[parent_idx]->data < maxHeapArray[idx]->data){
            swap(maxHeapArray[parent_idx] , maxHeapArray[idx]);
            swap(maxHeapArray[parent_idx]->maxHeapIdx , maxHeapArray[idx]->maxHeapIdx);

            heapifyUp(parent_idx);
        }
    }





    void heapifyDown(int idx){
        int left_idx = left(idx) , right_idx = right(idx);
        if(left_idx == -1)
            return;

        if(right_idx !=-1 and maxHeapArray[left_idx]->data > maxHeapArray[right_idx]->data){
            swap(maxHeapArray[left_idx] , maxHeapArray[right_idx]);
            swap(maxHeapArray[left_idx]->maxHeapIdx , maxHeapArray[right_idx]->maxHeapIdx);
        }
        if(maxHeapArray[idx]->data < maxHeapArray[left_idx]->data){
            swap(maxHeapArray[idx] , maxHeapArray[left_idx]);
            swap(maxHeapArray[idx]->maxHeapIdx , maxHeapArray[left_idx]->maxHeapIdx);

            heapifyDown(left_idx);
        }
    }




    void push(node* trgt){
        assert(!full());

        maxHeapArray[++current_idx] = trgt;
        maxHeapArray[current_idx]->maxHeapIdx = current_idx;

        heapifyUp(current_idx);
    }





    node* pop(){
        assert(!empty());

        swap(maxHeapArray[current_idx] , maxHeapArray[0]);
        swap(maxHeapArray[current_idx]->maxHeapIdx , maxHeapArray[0]->maxHeapIdx);

        current_idx--;

        heapifyDown(0);

        return maxHeapArray[current_idx + 1];
    }




    void pop_idx(int idx){
        assert(!empty() and idx <= current_idx);

        swap(maxHeapArray[idx] , maxHeapArray[0]);
        swap(maxHeapArray[idx]->maxHeapIdx , maxHeapArray[0]->maxHeapIdx);

        swap(maxHeapArray[current_idx] , maxHeapArray[0]);
        swap(maxHeapArray[current_idx]->maxHeapIdx , maxHeapArray[0]->maxHeapIdx);

        current_idx--;

        heapifyDown(0);
    }



    int top(){
        assert(!empty());

        return maxHeapArray[0]->data;
    }



    bool empty(){
        return current_idx == -1;
    }



    bool full(){
        return (current_idx + 1) == capacity;
    }
};






struct minMaxHeap{
    doublyLinkedList dll;
    minHeap *mnh{nullptr};
    maxHeap *mxh{nullptr};



    minMaxHeap(int capacity){
        mnh = new minHeap(capacity);
        mxh = new maxHeap(capacity);
    }



    int get_min(){
        return mnh->top();
    }



    int get_max(){
        return mxh->top();
    }




    void push(int data){
        node* new_node = new node(data);

        /**************************************************************
        push it to the doubly linked list then the min and the max heaps
        ***************************************************************/
        dll.push(new_node);
        mnh->push(new_node);
        mxh->push(new_node);
    }





    /************************************************************************
    used to fix the min and the max heaps(delete from them by the given index)
    *************************************************************************/
    void pop(int choice , int idx){
        if(choice == 1){
            mnh->pop_idx(idx);
        }else{
            mxh->pop_idx(idx);
        }
    }




    void pop_min(){
        node* trgt = mnh->pop();            //get the node address

        int maxHeapIdx = trgt->maxHeapIdx;  //get the node index in the max heap to delete it from there

        pop(2 , maxHeapIdx);                //delete the node from the max heap

        dll.pop(trgt);                      //delete it from the doubly linked list
    }




    void pop_max(){
        node* trgt = mxh->pop();            //get the node address

        int minHeapIdx = trgt->minHeapIdx;  //get the node index in the min heap to delete it from there

        pop(1 , minHeapIdx);                //delete the node from the min heap

        dll.pop(trgt);                      //delete it from the doubly linked list
    }



    /**********************
    free the reserved space
    ***********************/
    ~minMaxHeap(){
        //free the doubly linked list first then the arrays of the min and max heaps ,which are of pointers type
        while(dll.head){
            node* dummy_head = dll.head;
            dll.head = dll.head->next;
            delete dummy_head;
        }

        delete [] mnh->minHeapArray;
        delete [] mxh->maxHeapArray;
    }
};
