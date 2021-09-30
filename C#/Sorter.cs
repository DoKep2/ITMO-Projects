using System;

static class Sorter
{
    public static void Sort<T>(this T[] arr)
        where T : IComparable
    {
        for (int i = arr.Length - 1; i > 0; i--)
        {
            for (int j = 1; j <= i; j++)
            {
                T element1 = arr[j - 1];
                T element2 = arr[j];
                if (element1.CompareTo(element2) > 0)
                {
                    (arr[j], arr[j - 1]) = (arr[j - 1], arr[j]);
                }
            }
        }
    }
}

class Point : IComparable 
{
    private int X { get; set; }
    private int Y { get; set; }

    public Point(int x, int y)
    {
        X = x;
        Y = y;
    }
    public int CompareTo(object obj)
    {
        Point tmp = (Point) obj;
        if (X > tmp.X)
        {
            return 1;
        }
        else if (X < tmp.X)
        {
            return -1;
        }
        else if (Y > tmp.Y)
        {
            return 1;
        }
        else if (Y < tmp.Y)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    public override string ToString()
    {
        return string.Format("({0}, {1})", X, Y);
    }
}

public class Program
{
    
    static void Main(){
        Point[] a = new Point[]
        {
            new Point(2, 3), new Point(0, 5),
            new Point(7, 2), new Point(0, 4)
        };
        int[] c = new int[]{5, 3, 1, 0, 11, 2};
        string[] d = new string[] {"ASD", "ASDXZC", "QWE", "xzc"};
        Sorter.Sort(c);
        Sorter.Sort(d);
        foreach (var x in c)
        {
            Console.Write(x + " ");
        }

        Console.WriteLine();
        foreach (var x in d)
        {
            Console.Write(x + " ");
        }
    }
}
