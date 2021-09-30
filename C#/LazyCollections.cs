using System;
using System.Collections.Generic;
using System.Threading;

public class Sequences
{
    public static IEnumerable<int> Fibonacci
    {
        get
        {
            int previous = 1;
            int current = 1;
            yield return 1;
            yield return 1;
            while (true)
            {
                int value = previous + current;
                previous = current;
                current = value;
                yield return value;
            }
        }
    }
}

public class Program
{
    static void Main()
    {
        foreach (var x in Sequences.Fibonacci)
        {
            Thread.Sleep(100);
            Console.Write(x + " ");
            if (Console.KeyAvailable) break;
        }
    }
}