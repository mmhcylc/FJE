#include "json_processor/json_processor.h"

using namespace std;
json_processor::json_processor(){
    root=nullptr;
}

json_processor::~json_processor(){

}

string json_processor::output(json_outputer_factory* factory) {
    if (factory == nullptr || root == nullptr) return "";
    unique_ptr<json_outputer> outputerr(factory->create());
    outputerr->get_list_for_container(root.get(), 0);
    string result = outputerr->get_output_content();
    return result;
}


void json_processor::load(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        printf("open error!\n");
        return;
    }
    
    stringstream content_stream;
    content_stream << file.rdbuf(); // 将文件内容读入 stringstream

    // 关闭文件，避免资源泄漏
    file.close();

    string content = content_stream.str();

    size_t now_pos = 0;
    root = process_container(content, 0, now_pos);
}

int json_processor::ignore(string& data, size_t& index){
    index = data.find_first_not_of(" \r\n\t", index);
    if(index == string::npos){
        return 1;
    }
    else{
        return 0;
    }
}

string json_processor::get_next_text(string& data, size_t& index){
    string text;
    int t;
    if (data[index] == '\"'){
        //printf("11\n");
        index += 1;
        size_t last = data.find_first_of('\"', index);
        if (last == string::npos){
            printf("no \"\n");
            return "error";
        }
        t = last - index;
        text = data.substr(index, t);
        index = t + index + 1;
        return text;
    }
    else{
        //printf("22\n");
        size_t last = data.find_first_of(" \n\r\t,:", index);
        if (last == string::npos){
            printf("no ender\n");
            return "error";
        }
        t = last - index;
        text = data.substr(index, t);
        index = t + index;
        return text;
    }
}

shared_ptr<JsonLeaf> json_processor::process_leaf(string& data, size_t& index)
{
    shared_ptr<JsonLeaf> ans = make_shared<JsonLeaf>();
    string value = get_next_text(data, index);
    ans->set_value(value);
    return ans;
}

bool json_processor::is_valid_index(const string& data, size_t index) {
    return index < data.size();
}

bool json_processor::skip_whitespace(const string& data, size_t& index) {
    while (is_valid_index(data, index) && isspace(data[index])) {
        ++index;
    }
    return is_valid_index(data, index);
}

bool json_processor::expect_char(const string& data, size_t& index, char expected) {
    if (!skip_whitespace(data, index) || data[index] != expected) {
        cout << "Expected '" << expected << "' but found '" << data[index] << "'\n";
        return false;
    }
    ++index;
    return true;
}

shared_ptr<JsonContainer> json_processor::process_container(string& data, int level, size_t& index) {
    auto container = make_shared<JsonContainer>(level);

    if (!expect_char(data, index, '{')) {
        return nullptr;
    }

    while (true) {
        // Parse key
        if (!skip_whitespace(data, index)) {
            cout << "Unexpected end of input while seeking key.\n";
            return nullptr;
        }

        string key = get_next_text(data, index);

        // Check for ':' after key
        if (!expect_char(data, index, ':')) {
            return nullptr;
        }

        // Skip whitespace before value
        if (!skip_whitespace(data, index)) {
            cout << "Unexpected end of input while seeking value.\n";
            return nullptr;
        }

        // Value is a container, recursively call this function
        if (data[index] == '{') {
            shared_ptr<JsonContainer> child = process_container(data, level + 1, index);
            if (!child) {
                return nullptr;
            }
            child->set_content(key);
            container->append_child(child);
        }
        // Value is a leaf
        else {
            shared_ptr<JsonLeaf> child = process_leaf(data, index);
            if (!child) {
                return nullptr;
            }
            child->set_content(key);
            container->append_child(child);
        }

        // Skip whitespace before checking for ',' or '}'
        if (!skip_whitespace(data, index)) {
            cout << "Unexpected end of input after value.\n";
            return nullptr;
        }

        // Check for ',' or '}' indicating more items or end of object
        if (data[index] == ',') {
            ++index;
        } else if (data[index] == '}') {
            ++index;
            break;
        } else {
            cout << "Expected ',' or '}' but found '" << data[index] << "'\n";
            return nullptr;
        }
    }

    return container;
}


