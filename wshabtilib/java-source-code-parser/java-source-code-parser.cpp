#include <iostream>
#include <regex>
#include <string>
#include <fstream>

using namespace std ;

//----------------------------------------------------------------------------------------------------------------------------

string get_class_name(string source_code_path)
{
    std::ifstream source_input_file;
    source_input_file.open(source_code_path, std::ios_base::in);

    string search_string = "";
    string source_code = "";

    while(!source_input_file.eof())
	{
        getline(source_input_file, search_string);
        source_code.append(search_string);        
    }

    smatch sm ;

    //CLASS NAME REGEX (WITH CLASS|INTERFACE|ENUM)
    regex class_regex (R"rgx((class|interface|enum)\s([^\n\s]*))rgx");
    regex_search(source_code, sm, class_regex);
    string class_name_with_decl = ((string) sm[0]);
    string class_name = (class_name_with_decl.replace(0,class_name_with_decl.find(" ")+1, ""));
    return class_name;
 }

//----------------------------------------------------------------------------------------------------------------------------

vector<string> get_prototypes(string source_code_path)
{
    std::ifstream source_input_file;
    source_input_file.open(source_code_path, std::ios_base::in);

    string search_string = "";
    string source_code = "";
    vector<string> prototype;

    smatch sm ;

    //PROTOTYPE REGEX
    regex prototype_regex(R"rgx(((public|private|protected|static|final|native|synchronized|abstract|transient)+\s)+[\w\<\>\[\]]+\s+(\w+) *\([^\)]*\))rgx");
    
    while(!source_input_file.eof())
	{
        getline(source_input_file, search_string);
        source_code.append(search_string);        
    }

    while(regex_search(source_code, sm, prototype_regex))
    {
        prototype.push_back(sm[0]);
        source_code = sm.suffix();
    }

    return prototype;
}

//----------------------------------------------------------------------------------------------------------------------------

vector<string> get_method_and_values_name(string method_prototype)
{
    smatch sm;
    vector<string> method_values_name;
    regex method_and_value_name_regex (R"rgx(\b\w+(?=\s*[,()]))rgx");

    while(regex_search(method_prototype, sm, method_and_value_name_regex))
    {
        method_values_name.push_back(sm[0]);
        method_prototype = sm.suffix();
    }
    return method_values_name;
}

//----------------------------------------------------------------------------------------------------------------------------

string get_prototype_arguments(string method_prototype)
{
    //METHOD ARGUMENTS REGEX (WITH TYPES)
    string prototype_arguments = (method_prototype.replace(0,method_prototype.find("("), "")); 
    return prototype_arguments;
}

//----------------------------------------------------------------------------------------------------------------------------