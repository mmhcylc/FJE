#ifndef JSON_OUTPUTER_H
#define JSON_OUTPUTER_H

#include <string>
#include <vector>
using namespace std;
class JsonLeaf;
class JsonContainer;
class icon;

class json_outputer
{
protected:

    vector<string> output_content_list;
public:
    json_outputer();
    virtual void get_list_for_leaf(JsonLeaf* leaf, int level) = 0;
    virtual void get_list_for_container(JsonContainer* container, int level) = 0;
    string get_output_content();

    virtual ~json_outputer();
};

#endif