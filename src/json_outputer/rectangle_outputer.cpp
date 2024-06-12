#include "json_outputer/rectangle_outputer.h"
#include "json_processor/icon.h"
#include "json_processor/node.h"
#include <sstream>
using namespace std;

rectangle_outputer::rectangle_outputer(icon* input_icon) :json_outputer(){
    icon_rect=input_icon;
    len=0;
}

rectangle_outputer::~rectangle_outputer(){

}

void rectangle_outputer::get_list_for_leaf(JsonLeaf* jleaf, int layer) {
    
    ostringstream oss;
    size_t len_temp = layer * 3 + 3;
    if (icon_rect != nullptr) {
        oss << icon_rect->get_leaf_icon() << " ";
        len_temp += 2; // icon 和空格
    }

    oss << jleaf->get_content();
    len_temp += jleaf->get_content().length();

    if (jleaf->get_value() != "null") {
        oss << ": " << jleaf->get_value();
        len_temp =len_temp + 2 + jleaf->get_value().length(); // ": " 和 value 的长度
    }

    output_content_list.back() += oss.str();
    output_content_list.push_back("");

    len = max(len, len_temp);
}

size_t rectangle_outputer::char_num(const string& str) {
    size_t count = 0;
    string_view view(str);

    auto it = view.begin();
    while (it != view.end()) {
        unsigned char c = static_cast<unsigned char>(*it);
        if (c <= 0x7F) { // ASCII
            ++it;
        } else if ((c & 0xE0) == 0xC0) { // 2字节字符
            it += 2;
        } else if ((c & 0xF0) == 0xE0) { // 3字节字符
            it += 3;
        } else if ((c & 0xF8) == 0xF0) { // 4字节字符
            it += 4;
        } else {
            // 出现无效的 UTF-8 字符，可以选择处理错误或抛出异常。
            throw runtime_error("Invalid UTF-8 character encountered.");
        }
        ++count;
    }

    return count;
}


void rectangle_outputer::get_list_for_container(JsonContainer* container, int layer) {
    string line = "";
    size_t temp_length = layer * 3 + 3;

    if (container->get_content() != "") {
        if (icon_rect != nullptr) {
            output_content_list.back() += (icon_rect->get_container_icon() + " ");
            temp_length += 2;
        }
        output_content_list.back() += container->get_content();
        temp_length += container->get_content().length();
        len = max(len, temp_length);
        output_content_list.push_back("");
    }

    int child_count = container->get_children_num();
    for (int i = 0; i < child_count; i++) {
        update_before_text(layer, i);

        line = concatenate_before_text();

        if (!output_content_list.empty()) {
            output_content_list.back() += line;
        } 
        else {
            output_content_list.push_back(line);
        }
        
        auto child = container->get_jsonnode_by_index(i);
        child->draw(this, layer + 1);
    }

    if (layer == 0) {
        finalize_output();
    }
}

void rectangle_outputer::update_before_text(int depth, int index) {
    while (before_text.size() > depth && !before_text.empty()) {
        before_text.pop_back();
    }

    if (index == 0) {
        if (depth == 0) {
            before_text.push_back("┌─ ");
        } else {
            before_text.back() = "│  ";
            before_text.push_back("├─ ");
        }
    } else {
        if (depth != 0) {
            before_text.back() = "│  ";
        }
        before_text.push_back("├─ ");
    }
}

string rectangle_outputer::concatenate_before_text() {
    string result;
    for (const auto& text : before_text) {
        result += text;
    }
    return result;
}

void rectangle_outputer::finalize_output() {
    before_text[0] = "└──";

    for (int i = 1; i < before_text.size(); i++) {
        before_text[i] = "┴──";
    }

    string final_str = concatenate_before_text();
    output_content_list.back() += final_str;

    for (int i = 0; i < output_content_list.size(); i++) {
        size_t current_length = char_num(output_content_list[i]);
        output_content_list[i] += (i != output_content_list.size() - 1) ? " " : "─";

        for (int j = len - current_length - 2; j >= 0; j--) {
            output_content_list[i] += "─";
        }

        if (i == 0) {
            output_content_list[i] += "┐";
        } else if (i == output_content_list.size() - 1) {
            output_content_list[i] += "┘";
        } else {
            output_content_list[i] += "┤";
        }
    }
}
