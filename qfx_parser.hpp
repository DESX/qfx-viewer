#ifndef QFX_PARSER_H
#define QFX_PARSER_H
#include <string>
#include <unordered_map>
#include <ctime>

enum class ttypes{na,transfer,dividend,credit,debit,check,pos,deposit};

struct qfx_transaction
{
   ttypes type = ttypes::na;
   int64_t amount;
   std::string memo;
   std::string name;
   std::pair<std::time_t,int> date_posted;
};

struct qfx_file
{
   std::unordered_map<std::string, qfx_transaction> transactions;
   static qfx_file read(std::string file_name,int utc_offset);
};

#endif
