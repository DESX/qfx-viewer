#ifndef QFX_PARSER_H
#define QFX_PARSER_H
#include <string>

class qfx_file
{
public:
   static qfx_file read(std::string file_name);
};

#endif
