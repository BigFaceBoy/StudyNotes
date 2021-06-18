#ifndef QUEUE_H_
#define QUEUE_H_

template <class T> class QueueItem;

template <class Type> class Queue{
private:
    QueueItem<Type>  *front;
    QueueItem<Type>  *back;
public:
    Queue():front(0), back(0){}
    ~Queue();

    Type& remove();
    void  add(const Type&);

    bool  is_empty() const{
        return front == 0;
    }
    bool  is_full();
};

#endif

