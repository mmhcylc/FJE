#ifndef RECTANGLE_OUTPUTER_FACTORY_H
#define RECTANGLE_OUTPUTER_FACTORY_H

#include "json_outputer_factory.h"
#include "rectangle_outputer.h"
using namespace std;
class rectangle_outputer_factory :public json_outputer_factory {
public:
    rectangle_outputer_factory(const string& icon_path = "");
    virtual ~rectangle_outputer_factory();
    virtual json_outputer* create() ;
};

#endif