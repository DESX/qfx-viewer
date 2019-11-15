#include "qfx_parser.hpp"
#include <iostream>
#include <algorithm>
#include <stack>
#include <fstream>
using namespace std;
bool begins_with(string a,string b)
{
   if(b.size() > a.size()) return false;

   auto first_neq = mismatch(b.begin(),b.end(),a.begin());
   return (first_neq.first == b.end()); 
}
string  extract_closer(string inp)
{
   auto clos = inp.find_first_of("/");
   if(clos == 0)
      return inp.substr(clos+1);
   else
      return "";
}
pair<string,string> extract_tag(string inp)
{
   pair<string,string> ret;
   auto begin_c = inp.find_first_of("<");
   if(begin_c != string::npos) 
   {
      auto end_c = inp.find_first_of(">", begin_c);

      if(end_c != string::npos) 
      {
         ret.first = inp.substr(begin_c + 1, end_c - begin_c - 1);
         ret.second = inp.substr(end_c + 1, inp.size() - end_c);
      }
   }
   return ret;
}
bool ends_with(string a,string b)
{
   if(b.size() > a.size()) return false;
   auto first_neq = mismatch(b.begin(), b.end(), a.end() - b.size());
   return (first_neq.first == b.end()); 
}
qfx_file qfx_file::read(string file_name)
{
   cout << "parsing file: " << file_name << endl;
   cout << "T:" << begins_with("Hello","He") << endl;
   cout << "F:" << begins_with("Hello","Ha") << endl;
   cout << "T:" << ends_with("Hello","lo") << endl;
   cout << "F:" << ends_with("Hello","eo") << endl;

   ifstream infile_s(file_name);

   string line;
   int line_cnt = 0;
   if (infile_s.is_open())
   {
      stack stk<string>;
      while ( getline (infile_s, line) )
      {
         line_cnt++;
         if(line_cnt < 40)
         {
            auto tags = extract_tag(line);
            
            if(!tags.first.empty())   
            {
               auto end_tag = extract_closer(tags.first); 
               if(!end_tag.empty())
               {
                  cout << "ET: " << end_tag << endl;
                  if(!tags.second.empty())
                  {
                     cout << "ERROR: end tag with value" << endl;
                  }
               }
               else if(!tags.second.empty())
               {
                  cout << "VL: " << tags.first << ":" << tags.second << endl;
               }
               else
               {
                  cout << "ST: " << tags.first << endl;
                  if(!tags.second.empty())
                  {
                     cout << "ERROR: start tag with value" << endl;
                  }
               }
            }
         }
      }
      infile_s.close();
   }

   cout << "LINE CNT: " << line_cnt << endl;

   qfx_file file_descriptor;
   return file_descriptor;
}
