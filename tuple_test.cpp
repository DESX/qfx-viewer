#include <iostream>
#include <tuple>
using namespace std;

struct tuple_wraper
{
   std::tuple<int,double> v;
   tuple_wraper(tuple_wraper& other)
   {
      v = other.v;
   }
   tuple_wraper(tuple_wraper&& other)
   {
      v = other.v;
   }

   int operator < (const tuple_wraper & other) const
   {
      return (v < other.v);
   }
   int operator == (const tuple_wraper & other) const
   {
      return (v == other.v);
   }
};

int main()
{
   cout << "TUPLE TEST" << endl;
}
