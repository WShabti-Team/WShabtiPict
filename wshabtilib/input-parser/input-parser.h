#ifndef __INPUT_PARSER_H__
#define __INPUT_PARSER_H__

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////
 * Parses a parameter file formatted like:
 * 
 * parameter_name1:value_p1_1,value_p1_2,value_p1_3,...
 * parameter_name2:value_p2_1,value_p2_2,value_p2_3,...
 * ...
 * #CONSTRAINTS
 * value_p1_x,value_p2_x,value_p3_x,...
 * value_p1_y,value_p2_y,value_p3_y,...
 * ...
 * 
 * and builds a model_matrix containing on
 * ROWS : parameters
 * COLUMNS : values
 * 
 * [value_p1_1,value_p1_2,value_p1_3,...]
 * [value_p2_1,value_p2_2,value_p2_3,...]
 * [...]
 * 
 * WARNING : PARAMETER NAME IS LOST!
 * 
 * INPUT:
 *      file_stream
 *      parameter_matrix (DON'T ALLOCATE THIS OBJECT, JUST PASS vector<vector<string>> model_matrix)
 * 
 * OUTPUT:
 *      parameter_matrix built
 * 
*///////////////////////////////////////////////////////////////////////////////////////////////////////////
void parameter_parser(std::ifstream &input_file_stream, std::vector<std::vector<std::string>> &parameter_matrix);

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////
 * Parses a parameter file formatted like:
 * 
 * parameter_name1:value_p1_1,value_p1_2,value_p1_3,...
 * parameter_name2:value_p2_1,value_p2_2,value_p2_3,...
 * ...
 * #CONSTRAINTS
 * value_p1_x,value_p2_x,value_p3_x,...
 * value_p1_y,value_p2_y,value_p3_y,...
 * ...
 * 
 * and builds a constraint_matrix containing on
 * ROWS : exclused combination of values
 * COLUMNS : values to exclude
 * 
 * [value_p1_x,value_p2_x,value_p3_x,...]
 * [value_p1_y,value_p2_y,value_p3_y,...]
 * 
 * INPUT:
 *      file_stream
 *      constraint_matrix (DON'T ALLOCATE THIS OBJECT, JUST PASS vector<vector<string>> constraint_matrix)
 * 
 * OUTPUT:
 *      constraint_matrix built
 * 
*///////////////////////////////////////////////////////////////////////////////////////////////////////////
void constraint_parser(std::ifstream &input_file_stream, std::vector<std::vector<std::string>> &constraint_matrix);

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////
 * Parses a file formatted like:
 * 
 * parameter_name1:value_p1_1,value_p1_2,value_p1_3,...
 * parameter_name2:value_p2_1,value_p2_2,value_p2_3,...
 * ...
 * #CONSTRAINTS
 * value_p1_x,value_p2_x,value_p3_x,...
 * value_p1_y,value_p2_y,value_p3_y,...
 * ...
 * 
 * and builds a constraint_matrix and parameter_matrix (uses constraint_parser and parameter_parser)
 * 
 * INPUT:
 *      file_path
 *      parameter_matrix (DON'T ALLOCATE THIS OBJECT, JUST PASS vector<vector<string>> model_matrix)
 *      constraint_matrix (DON'T ALLOCATE THIS OBJECT, JUST PASS vector<vector<string>> constraint_matrix)
 * 
 * OUTPUT:
 *       parameter_matrix and constraint_matrix built
 * 
*///////////////////////////////////////////////////////////////////////////////////////////////////////////
void input_parser(std::string input_file_path, std::vector<std::vector<std::string>> &parameter_matrix, std::vector<std::vector<std::string>> &constraint_matrix);

#endif