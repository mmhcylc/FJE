#ifndef ICON_H
#define ICON_H

#include <string>
#include <fstream>

using namespace std;

class icon {
private:
    string leaf_icon;
    string container_icon;
public:
    icon(const string& path);
    ~icon();
    string get_container_icon();
    string get_leaf_icon();
};

#endif