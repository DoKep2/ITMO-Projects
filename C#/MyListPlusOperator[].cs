using System;
using System.Collections;

public class MyList<T> : IEnumerable
{
    private T[] arr;
    private int cnt = 0;

    public MyList()
    {
        arr = new T[100];
    }

    void Enlarge()
    {
        throw new NotImplementedException();
    }

    public void Add(T item)
    {
        if (cnt == arr.Length)
        {
            Enlarge();
        }

        arr[cnt] = item;
        cnt++;
    }

    public IEnumerator GetEnumerator()
    {
        for (int i = 0; i < cnt; i++)
        {
            yield return arr[i];
        }
    }

    public T this[int index]
    {
        get
        {
            if (index < 0 || index > cnt) throw new IndexOutOfRangeException();
            return arr[index];
        }
        set
        {
            if (index < 0 || index > cnt) throw new IndexOutOfRangeException();
            arr[index] = value;
        }
    }
    public int Cnt
    {
        get { return cnt; }
    }
}

public class Program
{
    static void Main()
    {
        MyList<int> lst = new MyList<int>();
        lst.Add(1);
        lst.Add(2);
        lst.Add(3);
        for (int i = 0; i < lst.Cnt; i++)
        {
            Console.WriteLine(lst[i]);
        }
    }
}