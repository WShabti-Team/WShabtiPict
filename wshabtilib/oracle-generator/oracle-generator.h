#ifndef __ORACLE_GENERATOR_H__
#define __ORACLE_GENERATOR_H__

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Takes a vector of oracles to check if AT LEAST one oracle is expressed as interval (e.g 11.0:0.12)
 * 
 * INPUT:
 *      vector of string (oracles)
 * 
 * OUTPUT:
 *      TRUE (FALSE): there's at least one (there's no) oracle expressed as interval
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool check_interval(std::vector<std::string> oracle);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Takes a csv input file with oracles (some could be specified as intervals) (e.g parameter1, parameter2, parameter3)
 * Creates a new output file containing appending oracle FOR EACH ROW (and delta if interval is specified) (e.g parameter1, parameter2, parameter3, oracle, (delta) )
 * (
 *  e.g row:1,3 oracle 4   -> 1,3,4
 *      row:1,3 oracle 4:5 -> 1,3,4,5
 * )
 * 
 * INPUT:
 * 
 * OUTPUT:
 *      
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void append_oracle_to_csv(std::vector<std::string> oracle, std::string input_file_path, std::string output_file_path);

#endif