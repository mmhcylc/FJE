#include "json_outputer/json_outputer_factory.h"
using namespace std;

json_outputer_factory::json_outputer_factory(const string& icon_path = ""){
    icon_ancestor = nullptr;
    if (icon_path != ""){
        icon_ancestor = new icon(icon_path);
    }
}
json_outputer_factory::~json_outputer_factory(){
    if (icon_ancestor != nullptr){
        delete icon_ancestor;
    } 
};