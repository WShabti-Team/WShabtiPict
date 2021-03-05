#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include "case-test-generator.h"
#include "../api/pictapi.h"
#include "../input-parser/input-parser.h"
#include "../utils/utils.h"

using namespace std;

void test_generator(int k_degree, string input_file, string output_file)
{
//----------------------------------------------------------------------------------------------------------------------------------------------------
  	
  	//FILE CONFIGURATION

  	std::ofstream test_case_output_file;

  	test_case_output_file.open(output_file, std::ios_base::out);

//----------------------------------------------------------------------------------------------------------------------------------------------------
  	
  	//PICT CONFIGURATION

    PICT_RET_CODE ret = PICT_SUCCESS;
    PICT_HANDLE task = PictCreateTask();
    PICT_HANDLE model = PictCreateModel();
    PictSetRootModel( task, model );

//----------------------------------------------------------------------------------------------------------------------------------------------------

    //CREATE MODEL

    vector<vector<string>> params_matrix;
    vector<vector<string>> constraints_matrix;
    
    input_parser(input_file, params_matrix, constraints_matrix);

    int number_of_parameters = params_matrix.size();
    PICT_HANDLE* parameters = new PICT_HANDLE[number_of_parameters];

    //Iterate on number of lines to get parameters 
    for(int index = 0; index<number_of_parameters; index++)
    {
        parameters[index] = PictAddParameter( model, params_matrix[index].size(), k_degree );
    }

//----------------------------------------------------------------------------------------------------------------------------------------------------
    
    //ADD CONSTRAINTS

    int number_of_constraints = constraints_matrix.size();
    PICT_EXCLUSION_ITEM** constraints = new PICT_EXCLUSION_ITEM*[number_of_constraints];

    int exclusions_count;
    int number_of_exclusion;
    for(int i = 0; i<number_of_constraints; i++)
    {
        exclusions_count = constraints_matrix[i].size();
    
        for(int j = 0; j < constraints_matrix[i].size(); j++)
        {
            if(constraints_matrix[i][j].compare("*") == 0 )
            {
                exclusions_count--;
            }
        }
        constraints[i] = new PICT_EXCLUSION_ITEM[exclusions_count];

        number_of_exclusion = exclusions_count;        

        for(int j = 0; j < constraints_matrix[i].size(); j++)
        {
            if( constraints_matrix[i][j].compare("*") != 0 )
            {
                constraints[i][exclusions_count-1].Parameter = parameters[j]; 
                constraints[i][exclusions_count-1].ValueIndex = position_in_vector(params_matrix[j], constraints_matrix[i][j]);                //params_matrix[j] -> vettore
                exclusions_count--; 
            }
        }
    
        PictAddExclusion( task, constraints[i], number_of_exclusion);
    }

//----------------------------------------------------------------------------------------------------------------------------------------------------

    //GENERATE RESULTS
    ret = PictGenerate( task );
    PICT_RESULT_ROW row = PictAllocateResultBuffer( task );
    size_t paramCount = PictGetTotalParameterCount( task );
    PictResetResultFetching( task );

//----------------------------------------------------------------------------------------------------------------------------------------------------

    //SAVE RESULTS 
    bool keep_reading = PictGetNextResultRow( task, row );
    while(keep_reading)
    {   
        for( size_t index = 0; index < paramCount-1; ++index )
        {
        	test_case_output_file << params_matrix[index][row[index]] << ",";
        }
        test_case_output_file << params_matrix[paramCount-1][row[paramCount-1]];

        keep_reading = PictGetNextResultRow( task, row );

        if(keep_reading == true)
        {
            test_case_output_file << endl;
        }
    }

//----------------------------------------------------------------------------------------------------------------------------------------------------

    //PICT DELETE 

    PictFreeResultBuffer( row );
    if( model != NULL )    {    PictDeleteModel( model ); }
    if( task != NULL )     {    PictDeleteTask( task );   }

//----------------------------------------------------------------------------------------------------------------------------------------------------

    //FILE CLOSING
    test_case_output_file.close();

//----------------------------------------------------------------------------------------------------------------------------------------------------
}