#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <filesystem>

#include "../wshabtilib/java-source-code-parser/java-source-code-parser.h"
#include "../wshabtilib/case-test-generator/case-test-generator.h"
#include "../wshabtilib/oracle-generator/oracle-generator.h"
#include "../wshabtilib/junit-test-case-generator/junit-test-case-generator.h"
#include "../wshabtilib/utils/utils.h"

#define PARAMETER_FILE "./tmp/model.txt"
#define TEST_CASE_FILE "./tmp/test_case.csv"

using namespace std;

int main()
{

//----------------------------------------------------------------------------------------------------------------------------------------------------

    //TAKE SOURCECODE PATH
    cout << "SourceCode Path: ";
    string source_code_path = "";
    cin >> source_code_path;

    //TAKE PROTOTYPE FORM SOURCECODE
    ofstream parameter_file;
    vector<string> prototypes = get_prototypes(source_code_path);
    vector<string> prototypes_tested;
    string possible_values_of_parameter = "";

    //TAKE CLASS NAME FORM PROTOTYPE
    string class_name = get_class_name(source_code_path);

    //CREATE DIRECTORY FOR CONTAINING FINAL FILES (.java class and .csv files)
    filesystem::create_directory("./JUnitTests/"+class_name);

//----------------------------------------------------------------------------------------------------------------------------------------------------

    //CREATE ALL TEST 
    for(auto prototype : prototypes)
    {
        //GET ALL POSSIBILE VALUES FOR PARAMETERS

        vector<string> method_and_values = get_method_and_values_name(prototype);
        string method_name = method_and_values[0];
        method_and_values.erase(method_and_values.begin()); //method name is saved in the variable so we can erase it from the vector and leave only parameters

        cout<<"\n-----METHOD: "<<prototype<<"-----"<<endl;
        cout<<"#Do you want skip this method? (y/n)"<<endl;
        string skip_choice = "n";
        do
        {

            cout<<"Please specify your choice: ";
            cin>>skip_choice;

        } while (skip_choice.compare("y") != 0 && skip_choice.compare("n")!= 0);

        //IF METHOD ISN'T SKIPPED
        if(skip_choice.compare("n")==0)
        {

            cout<<endl<<"#Do you want specify input file source? (y/n)"<<endl;
            string input_source = "n";
            do
            {

                cout<<"Please specify your choice: ";
                cin>>input_source;

            } while (input_source.compare("y") != 0 && input_source.compare("n")!= 0);

            parameter_file.open(PARAMETER_FILE, ios_base::out);
            prototypes_tested.push_back(prototype); //Method is added to the prototypes to test because it wasn't skipped

            //IF TERMINAL INPUT MODE IS CHOSEN
            if(input_source.compare("n") == 0)
            {
                for(auto parameter : method_and_values)
                {
                    cout<<endl<<"Please specify, separated by a comma, all possible values of \""<<parameter<<"\""<<endl ;
                    cout<<"For a range of numbers you can use the syntax \"start:stop:step\": ";
                    cin>>possible_values_of_parameter;

                    //IF LAST LINE
                    if(parameter.compare(method_and_values.back()) != 0)
                    {
                        parameter_file<<parameter<<":"<<possible_values_of_parameter<<endl;
                    }  
                    else
                    {
                        parameter_file<<parameter<<":"<<possible_values_of_parameter;
                    }
                }

                cout<<endl<<"#Do you want specify Exclusive Constraints? (y/n)"<<endl;
                string constraints_choice = "n";
                do
                {
                    cout<<"Please specify your choice: ";
                    cin>>constraints_choice;
                } while (constraints_choice.compare("y") != 0 && constraints_choice.compare("n")!= 0);
                
                //IF CONSTRAINTS ARE DESIRED
                if(constraints_choice.compare("y") == 0)   
                {  
                    parameter_file<<endl<<"#CONSTRAINTS";
                    cout<<endl<<"To specify a combination to exclude, use the syntax \"value1,value2,...\"."<<endl;
                    cout<<"Use \"*\" if you don't care about a parameter."<<endl;
                }

                string input_constraint = "";
                
                while(constraints_choice.compare("y") == 0)
                {
                    
                    cout<<endl<<"Please specify a combination to exclude or \"stop\" to terminate: ";
                    cin>>input_constraint;
                    //IF STRING "stop" is NOT used DURING CONSTRAINT SPECIFICATION
                    if(input_constraint.compare("stop") != 0)
                    {
                        parameter_file << endl << input_constraint;
                    }
                    else
                    {
                        break; //exit from while if word "stop" is used
                    }
                }
                parameter_file.close();
            }
            //IF FILE INPUT MODE IS CHOSEN
            else
            {
                cout<<"Please specify the parameter file path: ";
                string parameter_input_file_path = "";
                cin>>parameter_input_file_path;
                //---------COPY INPUT FILE IN THE OUTPUT DIRECTORY---------// 
                ifstream source(parameter_input_file_path, ios::binary);
                ofstream dest(PARAMETER_FILE, ios::binary);

                istreambuf_iterator<char> begin_source(source);
                istreambuf_iterator<char> end_source;
                ostreambuf_iterator<char> begin_dest(dest);

                copy(begin_source, end_source, begin_dest);

                source.close();
                dest.close();
                //---------COPY INPUT FILE IN THE OUTPUT DIRECTORY---------// 
            }

//----------------------------------------------------------------------------------------------------------------------------------------------------
            
            //GENERATE TEST CASES
            cout<<"\nPlease specify the order of combinations for \""<<method_name<<"\": ";
            int k_degree = 0;
            cin>>k_degree;

            test_generator(k_degree, PARAMETER_FILE, TEST_CASE_FILE);

//----------------------------------------------------------------------------------------------------------------------------------------------------

            //GET ALL POSSIBILE ORACLES
            ifstream test_case_input_file;
            test_case_input_file.open(TEST_CASE_FILE, std::ios_base::in);
            vector<string> oracle;
            string test_case = "";
            string test_case_oracle = "";

            cout<<"\n-----ORACLE: "<<prototype<<"-----"<<endl;
            cout<<"Please specify the oracle for the following possible combinations"<<endl;
            cout<<"For a range of numbers you can use the syntax \"expected_value:delta\""<<endl;

            while(!test_case_input_file.eof())
            {
                getline(test_case_input_file, test_case);
                cout<<method_name<<"("<<test_case<<"): ";
                cin>>test_case_oracle;
                oracle.push_back(test_case_oracle);
            }

            append_oracle_to_csv(oracle, TEST_CASE_FILE,"./JUnitTests/"+class_name+"/"+method_name+"_test.csv");
        }
    }

//----------------------------------------------------------------------------------------------------------------------------------------------------
    
    //CREATE JAVA TEST CLASS
    test_source_code_generate(source_code_path, "./JUnitTests/"+class_name+"/", class_name, prototypes_tested);

//----------------------------------------------------------------------------------------------------------------------------------------------------

    //CONCLUSION
    cout<<endl<<"Your tests have been generated, please check JUnitTests/ "<<endl;
    return 0;

//----------------------------------------------------------------------------------------------------------------------------------------------------
}