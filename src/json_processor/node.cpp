#include "json_processor/node.h"
#include "json_processor/icon.h"
#include "json_outputer/json_outputer.h"
using namespace std;

node::node(){
    content="";
}

node::~node(){

}

void node::set_content(const string& data){
    content=data;
}

string node::get_content(){
    return content;
}

int JsonContainer::get_children_num(){
    int ans=children.size();
    return ans; 
}

void JsonContainer::append_child(shared_ptr<node> c){
    children.push_back(c);
}

vector<shared_ptr<node>>& JsonContainer::get_children(){
    return children; 
}

shared_ptr<node>& JsonContainer::get_jsonnode_by_index(size_t index) {
    return children[index]; 
}

JsonContainer::JsonContainer(int level):node(){
    layer_count=level;
}

void JsonContainer::draw(json_outputer* json_renderer, int level){
    json_renderer->get_list_for_container(this, level);
}

JsonContainer::~JsonContainer(){

}

JsonLeaf::JsonLeaf() :node(){

}

JsonLeaf::~JsonLeaf(){
    
}

void JsonLeaf::set_value(const string& content){
    value_content = content;
}

string JsonLeaf::get_value(){
    return value_content; 
}

void JsonLeaf::draw(json_outputer* json_renderer, int level){
    json_renderer->get_list_for_leaf(this, level);
}


