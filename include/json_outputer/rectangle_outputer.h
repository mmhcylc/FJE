#ifndef RECTANGLE_OUTPUTER_H
#define RECTANGLE_OUTPUTER_H

#include "json_outputer.h"
#include <vector>
using namespace std;
class rectangle_outputer :public json_outputer
{
private:
    icon* icon_rect;
    size_t len;
    vector<string> before_text;

public:
    rectangle_outputer(icon* icon = nullptr);
    virtual void get_list_for_leaf(JsonLeaf* jleaf, int layer) ;
    virtual void get_list_for_container(JsonContainer* jcontainer, int layer) ;
    virtual ~rectangle_outputer();
private:
    size_t char_num(const string& str);
    void update_before_text(int depth, int index);
    string concatenate_before_text();
    void finalize_output();
};




#endif