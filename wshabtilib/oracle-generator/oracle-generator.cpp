#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "../utils/utils.h"

using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------------

bool check_interval(vector<string> oracle)
{
	for(string oracle_value : oracle)
	{
		if(oracle_value.find(':') != string::npos) //':' FOUND
      	{
			return true;
      	}
	}
	return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void append_oracle_to_csv(vector<string> oracle, string input_file_path, string output_file_path)
{
    ofstream output_file;
    ifstream input_file;
  	output_file.open(output_file_path, ios_base::out);
	input_file.open(input_file_path, ios_base::in);

    int index = 0;
    string combination = "";

    bool interval_found = check_interval(oracle);

	bool keep_reading = !input_file.eof();

	//---------------------------------------------------THESE LINES ARE FOR APPENDING ORACLES TO CSV FILE---------------------------------------------------
    while(keep_reading)
	{
		getline(input_file, combination);

		if(interval_found)
		{
			if(oracle[index].find(':') != string::npos) //':' FOUND - JUST APPEND
			{
				vector<string> expected_delta = split(oracle[index++], ":");
				output_file<<combination <<","<<expected_delta[0]<<","<<expected_delta[1];
			}
			else
			{
				output_file<<combination <<","<<oracle[index++]<<",0"; //':' NOT FOUND - CREATE NULL DELTA
			}
		}
        
		else
		{
			output_file<<combination <<","<<oracle[index++];
		}

		keep_reading = !input_file.eof();
        if(keep_reading)
        {
          	output_file<<endl;
        }           
    }
	//---------------------------------------------------THESE LINES ARE FOR APPENDING ORACLES TO CSV FILE---------------------------------------------------

    input_file.close();
    output_file.close();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------