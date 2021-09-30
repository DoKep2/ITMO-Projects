using System;
using System.Collections;
using System.Collections.Generic;

public class QueueItem<T>
{
    public T value { get; set; }
    public QueueItem<T> next { get; set; }

    public QueueItem(T value)
    {
        this.value = value;
        this.next = null;
    }
}

public class Queue<T> : IEnumerable<T>
{
    public QueueItem<T> head { get; set; }
    public QueueItem<T> tail { get; set; }

    public void Push(T value)
    {
        QueueItem<T> tmp = new QueueItem<T>(value);
        if (head == null)
        {
            head = tail = tmp;
        }
        else
        {
            tail.next = tmp;
            tail = tmp;
        }
    }

    public T Pop()
    {
        if (head == null)
        {
            throw new Exception("Queue is empty");
        }

        var res = head.value;
        head = head.next;
        if (head == null)
        {
            tail = null;
        }
        return res;
    }

    public IEnumerator<T> GetEnumerator()
    {
        return new QueueEnumenator<T>(this);
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }
}

public class QueueEnumenator<T> : IEnumerator<T>
{
    private Queue<T> queue;
    private QueueItem<T> item;
    public QueueEnumenator(Queue<T> queue)
    {
        this.queue = queue;
        item = null;
    }
    public T Current
    {
        get { return item.value; }
    }
    public bool MoveNext()
    {
        if (item == null)
        {
            item = queue.head;
        }
        else
        {
            item = item.next;
        }

        return item != null;
    }

    public void Reset()
    {
        
    }
    public void Dispose()
    {
        
    }
    object IEnumerator.Current => Current;
}

public class Program
{
    static void Main()
    {
        var q = new Queue<int>();
        q.Push(1);
        q.Push(2);
        q.Push(3);
        foreach (var x in q)
        {
            Console.WriteLine(x);
        }
    }
}