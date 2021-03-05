#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "input-parser.h"
#include "../utils/utils.h"

using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------------

void input_parser(string input_file_path, vector<vector<string>> &parameter_matrix, vector<vector<string>> &constraint_matrix)
{
	
	std::ifstream input_file;
  	input_file.open(input_file_path, std::ios_base::in);

	parameter_parser(input_file, parameter_matrix);
	constraint_parser(input_file, constraint_matrix);
	
	input_file.close();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void constraint_parser(ifstream &input_file_stream, vector<vector<string>> &constraint_matrix)
{
	string file_row;
	int num_of_params = 0;

	while(!input_file_stream.eof())
	{	
		getline(input_file_stream, file_row);
		if(start_string_delim_find(file_row,'#'))
		{
			break;
		}

		vector<string> values_vector = split(file_row, ",");
	    constraint_matrix.push_back(vector<string>());

		for (auto value : values_vector)
		{
			constraint_matrix[num_of_params].push_back(value);
		}

		num_of_params++;
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void parameter_parser(ifstream &input_file_stream, vector<vector<string>> &parameter_matrix)
{
	string file_row;
	int num_of_params = 0;

	while(!input_file_stream.eof())
	{
		getline(input_file_stream, file_row);
		if(start_string_delim_find(file_row,'#'))
		{
			break;
		}

		string extracted_values = file_row.substr(file_row.find(':')+1); //pick only values of the params in the line (after ':' )
		vector<string> values_vector = split(extracted_values, ",");
	    parameter_matrix.push_back(vector<string>());

		//------------------------------------------THESE LINES ARE FOR CHECKING FOR RANGE INPUT IN FORMAT START:STOP:STEP AND INSERT INTO MODEL MATRIX------------------------------------------
		for (string value : values_vector)
		{
			if(value.find(':') == string::npos)
			{
				parameter_matrix[num_of_params].push_back(value);
			}
			else
			{
				vector<string> start_stop_step = split(extracted_values, ":");
				if(value.find('.') == string::npos)
				{
					for(int i= stoi(start_stop_step[0]); i<= stoi(start_stop_step[1]); i = i + stoi(start_stop_step[2]))
					{
						parameter_matrix[num_of_params].push_back(to_string(i));
					}
				}
				else
				{
					for(float i= stof(start_stop_step[0]); i<= stof(start_stop_step[1]); i = i + stof(start_stop_step[2]))
					{
						parameter_matrix[num_of_params].push_back(to_string(i));
					}
				} 
			}
		}
		//------------------------------------------THESE LINES ARE FOR CHECKING FOR RANGE INPUT IN FORMAT START:STOP:STEP AND INSERT INTO MODEL MATRIX------------------------------------------
		num_of_params++;
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------