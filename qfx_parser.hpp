#ifndef QFX_PARSER_H
#define QFX_PARSER_H
#include <string>
#include <unordered_map>
#include <ctime>
#include <tuple>

enum class ttypes{na,transfer,dividend,credit,debit,check,pos,deposit};
enum class qfields{amount,memo,data};

struct qfx_transaction
{
   ttypes type = ttypes::na;
   int64_t amount = 0;
   std::string memo;
   std::string name;
   std::pair<std::time_t,int> date_posted;
};
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

struct qfx_file
{
   std::unordered_map<std::string, qfx_transaction> transactions;

   static qfx_file read(std::string file_name, int utc_offset);
   static std::vector<std::string> create_ordering(const qfx_file&,const std::vector<qfields>);
};

#endif
