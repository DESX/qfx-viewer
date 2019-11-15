#include "qfx_parser.hpp"
#include <iostream>
#include <algorithm>
#include <stack>
#include <fstream>
using namespace std;
int64_t get_amount(string inp)
{
   auto dot = inp.find_first_of(".");
   if(dot == inp.size()-3)
   {
      inp.erase(dot,1);
      try 
      {
         return stoll(inp);
      }
      catch (const std::invalid_argument& ia){cout << ia.what() << endl;}
      catch (const std::out_of_range& oor) {cout << oor.what() << endl;}

   }
   return 0;
}

pair<time_t, int> qfx_date_extract(string inp, int utc_offset)
{
   pair<time_t,unsigned int> ret;
   if(inp.size() != 18)    
   {
      cout << "ERROR, date not correct len: "<< inp.size() << endl;
      return ret;

   }
   if(inp.at(14) != '.') 
   {
      cout << "ERROR, date does not have dot in the right spot" << endl;
      return ret;
   }
   try 
   {
      tm t;
      t.tm_year  = stoi(inp.substr( 0, 4)) - 1900;
      t.tm_mon   = stoi(inp.substr( 4, 2));
      t.tm_mday  = stoi(inp.substr( 6, 2));
      t.tm_hour  = stoi(inp.substr( 8, 2)) + utc_offset;
      t.tm_min   = stoi(inp.substr(10, 2));
      t.tm_sec   = stoi(inp.substr(12, 2));
      ret.second = stoi(inp.substr(15, 3));
      ret.first =  mktime(&t);
   }
   catch (const std::invalid_argument& ia){cout << ia.what() << endl;}
   catch (const std::out_of_range& oor) {cout << oor.what() << endl;}

   return ret;
}
bool begins_with(string a, string b)
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
qfx_file qfx_file::read(string file_name, int utc_offset)
{
   ifstream infile_s(file_name);

   qfx_file fd;
   string line;
   int line_cnt = 0;
   if (infile_s.is_open())
   {
      stack<string> xml_stack;

      string curr_transaction_id;
      qfx_transaction curr_transaction;

      while( getline (infile_s, line) )
      {
         line_cnt++;
         bool in_transaction = false;
         auto tags = extract_tag(line);
         
         if(!tags.first.empty())   
         {
            auto end_tag = extract_closer(tags.first); 

            if(!end_tag.empty())
            {
               //closing tag
               if(!xml_stack.empty())
               {
                  auto val = xml_stack.top();
                  xml_stack.pop();
                  if(end_tag == val)
                  {
                     if(end_tag == "STMTTRN")
                     {
                        //if ending a transaction record, we place it in the list
                        if(!curr_transaction_id.empty())
                        {
                          auto found = fd.transactions.find(curr_transaction_id);
                          if(found == fd.transactions.end())
                          {
                              fd.transactions[curr_transaction_id] = curr_transaction;
                              curr_transaction_id = string();
                              curr_transaction = qfx_transaction();
                          }
                        }
                        else
                        {
                           cout << "ERROR: EMPTY TRANSACTION" << endl;
                        }
                     }
                  }
                  else
                  {
                     cout << "ERROR: " << end_tag << " does not match " << val <<  endl;
                     exit(EXIT_FAILURE);
                  }
               }
               else
               {
                  cout << "ERROR, xml stack empty" << endl;
                  exit(EXIT_FAILURE);
               }
               if(!tags.second.empty())
               {
                  cout << "ERROR: end tag with value" << endl;
               }
            }
            else if(!tags.second.empty())
            {
               //tag with a value
               if(xml_stack.top() == "STMTTRN")
               {
                  if(tags.first == "TRNTYPE") 
                  {
                          if(tags.second == "CREDIT") curr_transaction.type = ttypes::credit; 
                     else if(tags.second == "DEBIT" ) curr_transaction.type = ttypes::debit; 
                     else if(tags.second == "POS"   ) curr_transaction.type = ttypes::pos; 
                     else if(tags.second == "CHECK" ) curr_transaction.type = ttypes::check; 
                     else if(tags.second == "DEP"   ) curr_transaction.type = ttypes::deposit; 
                     else if(tags.second == "XFER"  ) curr_transaction.type = ttypes::transfer; 
                     else if(tags.second == "DIV"   ) curr_transaction.type = ttypes::dividend; 
                     else cout << "WARNING: UNKNOWN TRANSACTION TYPE: " << tags.second << endl;
                  }
                  else if(tags.first == "DTPOSTED") 
                  {
                     curr_transaction.date_posted = qfx_date_extract(tags.second, utc_offset);
                  }
                  else if(tags.first == "TRNAMT") 
                  {
                     curr_transaction.amount = get_amount(tags.second);
                  }
                  else if(tags.first == "FITID") 
                  {
                     curr_transaction_id = tags.second;
                  }
                  else if(tags.first == "NAME") 
                  {
                     curr_transaction.name = tags.second;
                  }
                  else if(tags.first == "MEMO") 
                  {
                     curr_transaction.memo = tags.second;
                  }
                  else if(tags.first == "CHECKNUM") 
                  {

                  }
                  else
                  {
                     cout << "WARNING: UNKNOWN TRANSACTION PROPERTY: " << tags.first << endl;
                  }
               }
            }
            else
            {
               //open tag
               xml_stack.push(tags.first);
               if(!tags.second.empty())
               {
                  cout << "ERROR: start tag with value" << endl;
                  exit(EXIT_FAILURE);
               }
            }
         }
      }
      infile_s.close();
   }
   
   //cout << "LINE CNT: " << line_cnt << endl;
   //cout << "TRANSACTION CNT: " << fd.transactions.size() << endl;

   //for(auto & i:fd.transactions)
   //{
   //   cout << i.second.amount << ":" << i.first << endl; 
   //}

   return fd;
}
