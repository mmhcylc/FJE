#include <iostream>
#include <string>

#include "json_processor/icon.h"
#include "json_processor/json_processor.h"
#include "json_outputer/tree_outputer_factory.h"
#include "json_outputer/rectangle_outputer_factory.h"


using namespace std;
int main(int argc, char *argv[])
{
    string x=argv[1];
    string content;
    string file_name="",style="",icon_file_name="";

    if(x != "fje"){
        printf("command error\n");
        printf("%s\n", x.c_str());
        return 0;
    }

    for(int i=1;i<argc;i++){
        x=argv[i];
        if(i%2==0 && x=="-f"){
            file_name=argv[i+1];
        }
        else if(i%2==0 && x=="-s"){
            style=argv[i+1];
        }
        else if(i%2==0 && x=="-i"){
            icon_file_name=argv[i+1];
        }
    }
    if(file_name==""){
        printf("file_name error\n");
        return 0;
    }

    json_processor processor;
    processor.load(file_name);

    if(style == "tree"){
        tree_outputer_factory tree_factory(icon_file_name);
        content = processor.output(&tree_factory);
        printf("%s\n", content.c_str());
    }
    else if(style == "rectangle"){
        rectangle_outputer_factory rect_factory(icon_file_name);
        content = processor.output(&rect_factory);
        printf("%s\n", content.c_str());
    }
    else {
        printf("style error\n");
        return 0;
    }
    //停在显示界面
    cin.get();
    return 0;
}