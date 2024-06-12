#ifndef TREE_OUTPUTER_FACTORY_H
#define TREE_OUTPUTER_FACTORY_H

#include "json_outputer_factory.h"
#include "tree_outputer.h"
using namespace std;
class tree_outputer_factory :public json_outputer_factory {
public:
    tree_outputer_factory(const string& icon_file = "");
    virtual ~tree_outputer_factory();
    virtual json_outputer* create() ;
    
};

#endif