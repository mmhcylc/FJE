#include "json_outputer/tree_outputer_factory.h"
using namespace std;
tree_outputer_factory::tree_outputer_factory(const string& icon_file) :json_outputer_factory(icon_file){

}

tree_outputer_factory::~tree_outputer_factory(){

}

json_outputer* tree_outputer_factory::create(){
    tree_outputer* ans=new tree_outputer(icon_ancestor);
    return ans;
}



