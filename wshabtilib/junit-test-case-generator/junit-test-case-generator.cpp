#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

#include "../java-source-code-parser/java-source-code-parser.h"

using namespace std ;

//----------------------------------------------------------------------------------------------------------------------------------------------------

string add_oracle_to_arguments(string prototype, bool interval_found)
{
    string arguments_with_oracle = "";
    if(interval_found)
    {
        arguments_with_oracle = (prototype.replace(prototype.find(")"),prototype.find(")"), ", double oracle, double delta)")); 

    }
    else
    {
        arguments_with_oracle = (prototype.replace(prototype.find(")"),prototype.find(")"), ", Object oracle)")); 
    }
    return arguments_with_oracle;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

bool delta_check(string input_file_path, int num_of_parameters)
{
    ifstream test_with_oracle;
  	test_with_oracle.open(input_file_path, ios_base::in);
    string combination = "";

    while(!test_with_oracle.eof())
    {
        getline(test_with_oracle, combination);

        if((int) count(combination.begin(), combination.end(), ',') == (num_of_parameters + 1)) //If there's delta it is TRUE (+1 parameter)
        {
            test_with_oracle.close();
            return true;
        }
    }

    test_with_oracle.close();
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

string method_test_case_generate(string input_file_path, string method_prototype , string class_name)
{
    vector<string> method_and_values = get_method_and_values_name(method_prototype);
    string prototype_arguments = get_prototype_arguments(method_prototype);
    string method_name = method_and_values[0];

    bool interval_found = delta_check(input_file_path+"/" + method_name + "_test.csv", method_and_values.size()-1); //WARNING : DELTA CHECK PATH ISN'T THE SAME AS INPUT_FILE_PATH BECAUSE IT SEARCHES FOR THE SPECIFIC FILE [method_name]_test.csv REFERRED TO THE METHOD

    string init_of_method_test = "\n\n\t@ParameterizedTest"
                                 "\n\t@CsvFileSource(resources = \"./" + method_name + "_test.csv\")"
                                 "\n\tpublic void test_" + method_name + add_oracle_to_arguments(prototype_arguments, interval_found) + "{";
    string body_of_method_test = "\n\t\t" + class_name + " " + class_name + "Test = new " + class_name + "();";
    
    string assert_of_method_test = "";

    if(interval_found)
    {
        assert_of_method_test = "\n\t\tassertEquals(oracle," + class_name + "Test."+ method_name + "(";
    }
    else
    {
        assert_of_method_test = "\n\t\tassertEquals(String.valueOf(oracle), String.valueOf(" + class_name + "Test."+ method_name + "(";
    }
    
    //ADD ARGUMENTS
    for(int i = 1; i < method_and_values.size() ; i++ )
    {
        assert_of_method_test = assert_of_method_test + method_and_values[i];
        if(i != method_and_values.size()-1)
        {
            assert_of_method_test = assert_of_method_test + ", ";
        }
    }

    if(interval_found)
    {
        assert_of_method_test = assert_of_method_test + "),delta, \""+ method_name + " FAILED\");" + "\n\t}";
    }
    else
    {
        assert_of_method_test = assert_of_method_test + ")),\""+ method_name + " FAILED\");" + "\n\t}";
    }
  
    return (init_of_method_test + body_of_method_test + assert_of_method_test);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void test_source_code_generate(string input_file_path, string output_file_path, string test_class_name, vector<string> prototypes)
{
    string import_test = "import static org.junit.jupiter.api.Assertions.assertEquals;"
                         "\nimport org.junit.jupiter.params.ParameterizedTest;"
                         "\nimport org.junit.jupiter.params.provider.CsvFileSource;";
    string init_of_class = "\n\nclass " + test_class_name +"Test {";
    string end_of_class = "\n}";
    
    string test_source_code = import_test + init_of_class;
    string class_name = get_class_name(input_file_path);

    for(int i =0; i < prototypes.size(); i++)
    {
        test_source_code = test_source_code + method_test_case_generate(output_file_path, prototypes[i], class_name);
    }
    
    test_source_code = test_source_code + end_of_class;

    //CREATE .java TEST FILE
    ofstream java_test_class;
  	java_test_class.open(output_file_path + class_name + "Test.java", ios_base::out);
    java_test_class << test_source_code;
    java_test_class.close();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------