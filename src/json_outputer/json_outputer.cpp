#include "json_outputer/json_outputer.h"
using namespace std;
json_outputer::json_outputer(){

}

json_outputer::~json_outputer(){

}

string json_outputer::get_output_content(){
    string result;
    for (auto it = output_content_list.begin(); it != output_content_list.end(); ++it) {
        result += *it;
        result += "\n";
    }
    return result;
}


