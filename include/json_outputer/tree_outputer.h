#ifndef TREE_OUTPUTRT_H
#define TREE_OUTPUTRT_H

#include "json_outputer.h"
#include <vector>
using namespace std;
class tree_outputer :public json_outputer {
private:
    icon* icon_tree;
    vector<string> before_text;
    int if_final_child;
public:
    tree_outputer(icon* input_icon = nullptr);
    virtual void get_list_for_leaf(JsonLeaf* leaf, int level) ;
    virtual void get_list_for_container(JsonContainer* container, int level) ;
    virtual ~tree_outputer();

private:
    void adjust_before_text(int level, int child_count);
    void update_branch_prefix(int level, int currentIndex, int child_count);
    void append_to_output();
};

#endif