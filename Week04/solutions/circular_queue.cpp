class MyCircularQueue {
private:
    int arr[100];
    int front;
    int back; // points one after last
    int capacity;
public:
    MyCircularQueue(int k) {
        if (k > 100)
            k = 100;
        capacity = k;
        front = -1;
        back = -1;
    }
    
    bool enQueue(int value) {
        if (isFull())
            return false;
        if (isEmpty())
            front = back = 0;
        arr[back] = value;
        back = (back + 1) % capacity;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty())
            return false;
        // This was : front == back - 1, but it fails in wrap around cases
        if ((front + 1) % capacity == back) {
            front = back = -1;
            return true;
        }
        
        front = (front + 1) % capacity;
        return true;
    }

    int Size() {
        if (front == -1)
            return 0;
        if (back >= front)
            return back - front;
        return capacity - front + back;
    }
    
    int Front() {
        if (isEmpty())
            return -1;
        return arr[front];
    }
    
    int Rear() {
        if (isEmpty())
            return -1;
        // Was arr[back], but our implementation makes it so that the back points one after last
        return arr[(back - 1 + capacity) % capacity];
    }
    
    bool isEmpty() {
        return front == -1;
    }
    
    bool isFull() {
        if (back == front && back == 0 && front == 0)
            return true;
        // We did this as : front == back - 1, which was false, and we didnt had time to see why
        if ((back + 1) % capacity == front)
            return true;
        return false;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */