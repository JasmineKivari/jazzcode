using System;

namespace Lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            String str = "";
            for (int i = 1; i <= 100; i++)
            {
                if (i % 3 == 0 && i % 5 == 0)
                {
                    str += "FizzBuzz,";
                }
                
                if (i == 100)
                {

                    if (i % 3 == 0)
                    {
                        str += "Fizz";
                    }
                    if (i % 5 == 0)
                    {
                        str += "Buzz";
                    }

                    continue;
                }
                if (i % 3 == 0)
                {
                    str += "Fizz,";
                    continue;
                }
                if (i % 5 == 0)
                {
                    str += "Buzz,";
                    continue;
                }
                str += i + ",";
                
            }
            Console.WriteLine(str);
            Console.ReadLine();
            
        }
    }
}




