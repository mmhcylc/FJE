#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <memory>

using namespace std;
class icon;
class json_outputer;

class node {
protected:
    string content;
public:
    node();
    virtual ~node();
    void set_content(const string& data);
    string get_content();
    virtual void draw(json_outputer* json_renderer, int level) = 0;
};

class JsonContainer :public node {
private:
    vector<shared_ptr<node>> children;
    int layer_count;

public:
    JsonContainer(int level);
    virtual ~JsonContainer();
    int get_children_num();
    void append_child(shared_ptr<node> node);
    
    shared_ptr<node>& get_jsonnode_by_index(size_t index);

    vector<shared_ptr<node>>& get_children();

    virtual void draw(json_outputer* json_renderer, int level);

};

class JsonLeaf :public node {
private:
    string value_content;
public:
    JsonLeaf();
    virtual ~JsonLeaf();
    void set_value(const string& value);
    string get_value();
    virtual void draw(json_outputer* json_renderer, int level);

};

#endif