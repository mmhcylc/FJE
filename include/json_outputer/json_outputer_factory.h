#ifndef JSON_OUTPUTER_FACTORY_H
#define JSON_OUTPUTER_FACTORY_H
               
#include "json_outputer.h"
#include "json_processor/icon.h"
using namespace std;
class json_outputer_factory {
protected:
    icon* icon_ancestor;
public:
    json_outputer_factory(const string& icon_path);
    virtual json_outputer* create() = 0;
    ~json_outputer_factory();
};

#endif