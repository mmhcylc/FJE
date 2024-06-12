#include "json_processor/icon.h"
using namespace std;
icon::icon(const string& path){
    ifstream file(path);
    if (!file.is_open())
    {
        leaf_icon = "";
        container_icon = "";
        printf("open file error!\n");
    }
    string s1,s2;
    getline(file, s1);
    getline(file, s2);
    leaf_icon = s1;
    container_icon = s2;
    file.close();
}

icon::~icon(){

}

string icon::get_leaf_icon(){
    return leaf_icon;
}

string icon::get_container_icon(){
    return container_icon;
}


