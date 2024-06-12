#ifndef JSON_PROCESSOR_H
#define JSON_PROCESSOR_H

#include "node.h"
#include "json_outputer/json_outputer.h"
#include "json_outputer/json_outputer_factory.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
using namespace std;


class json_processor {
private:
    shared_ptr<JsonContainer> root;

public:
    json_processor();
    ~json_processor();
    string output(json_outputer_factory* factory);
    void load(const string& path);

private:
    string get_next_text(string& data, size_t& index);
    int ignore(string& data, size_t& index);

    shared_ptr<JsonContainer> process_container(string& data, int level, size_t& index);

    shared_ptr<JsonLeaf> process_leaf(string& data, size_t& index);

    bool is_valid_index(const string& data, size_t index);
    bool skip_whitespace(const string& data, size_t& index);
    bool expect_char(const string& data, size_t& index, char expected);
};



#endif