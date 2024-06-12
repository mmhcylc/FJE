#include "json_outputer/rectangle_outputer_factory.h"
using namespace std;
rectangle_outputer_factory::rectangle_outputer_factory(const string& icon_path) :json_outputer_factory(icon_path){

}

rectangle_outputer_factory::~rectangle_outputer_factory(){
    
}

json_outputer* rectangle_outputer_factory::create(){
    rectangle_outputer* ans=new rectangle_outputer(icon_ancestor);
    return ans;
}

