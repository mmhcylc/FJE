#include "json_outputer/tree_outputer.h"
#include "json_processor/icon.h"
#include "json_processor/node.h"
using namespace std;
tree_outputer::tree_outputer(icon* input_icon) :json_outputer(){
    icon_tree=input_icon;
    if_final_child=2;
}

tree_outputer::~tree_outputer(){

}

void tree_outputer::get_list_for_leaf(JsonLeaf* leaf, int level) {
    string line;
    // 添加叶子图标（如果存在）
    if (icon_tree != nullptr) {
        line += icon_tree->get_leaf_icon() + " ";
    }
    // 添加叶子内容
    line += leaf->get_content();
    // 如果叶子有值，添加值
    if (leaf->get_value() != "null") {
        line += ": " + leaf->get_value();
    }
    // 更新输出内容列表
    if (!output_content_list.empty()) {
        output_content_list.back() += line;
    } else {
        output_content_list.push_back(line);
    }
    // 添加新行
    output_content_list.push_back("");
}

void tree_outputer::get_list_for_container(JsonContainer* container, int level) {
    if (container->get_content() != "") {
        if (icon_tree != nullptr) {
            output_content_list.back() += (icon_tree->get_container_icon() + " ");
        }
        output_content_list.back() += container->get_content();
        output_content_list.push_back("");
    }

    int child_count = container->get_children_num();
    adjust_before_text(level, child_count);

    for (int i = 0; i < child_count; ++i) {
        update_branch_prefix(level, i, child_count);
        append_to_output();

        auto child = container->get_jsonnode_by_index(i);
        child->draw(this, level + 1);
    }
}

void tree_outputer::adjust_before_text(int level, int child_count) {
    while (before_text.size() > level - 1 && before_text.size() > 0) {
        before_text.pop_back();
    }
    before_text.push_back(if_final_child ? "   " : "│  ");
    if_final_child = (child_count == 1);
}

void tree_outputer::update_branch_prefix(int level, int currentIndex, int child_count) {
    while (before_text.size() > level && before_text.size() > 0) {
        before_text.pop_back();
    }
    before_text.push_back((currentIndex == child_count - 1) ? "└─ " : "├─ ");
    if_final_child = (currentIndex == child_count - 1);
}

void tree_outputer::append_to_output() {
    string str;
    for (const auto& s : before_text) {
        str += s;
    }
    if (!output_content_list.empty()) {
        output_content_list.back() += str;
    } else {
        output_content_list.push_back(str);
    }
}


