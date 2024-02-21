#include "list.h"
#include <iostream>

int main()
{
   list <int> c0;
   list <int> c1(3);
   list <int> c2(5, 2);
   c0.print();
   c1.print();
   c2.print();
   list <int> c4(c2);
   c4.print();
   list <int> c5 = c1;
   c5.print();
   c5.push_back(5);
   c5.push_front(4);
   c5.pop_front();
   c5.insert(c5.begin()++, 10);
   c5.erase(c5.begin()++);
   c5.reverse();
   c5.resize(2);
   c5.push_back(4);
   c5.push_back(5);
   c5.push_back(6);
   c5.push_back(0);
   c5.push_back(4);
   c5.remove(4);
   for (Iterator<int> it = c5.begin(); it != c5.end(); it++)
   {
       std::cout << *it << ' ';
   }
   std::cout << std::endl;
}