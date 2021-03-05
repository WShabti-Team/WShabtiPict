#ifndef __UTILS_H__
#define __UTILS_H__

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////
 * Tokenizes a row splitting the string in substrings (using a delimiter), puts every substring in the vector
 * 
 * INPUT:
 *	string to split
 *	delimiter (used for dividing string into substrings)
 *
 *	OUTPUT:
 *	-vector<string>
 *
*///////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::string> split (std::string s, std::string delimiter);

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////
 * Takes a vector and a string, returns element position in the vector 
 * 
 * INPUT:
 *	    vector: in which string should be found
 *	    target: string for which we want the position 
 *
 *	OUTPUT:
 *	    position : if string is in the vector
 *      -1       : if string is NOT in the vector     
 * 
*///////////////////////////////////////////////////////////////////////////////////////////////////////////
int position_in_vector(std::vector<std::string> vect, std::string target);

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////
 * Checks if delimiter character is at the START (first character) of string line
 * 
 * INPUT:
 *	    string
 *
 *	OUTPUT:
 *	    TRUE : if first character of the string IS the delimiter
 *      FALSE : if first character of the string is NOT the delimiter
 * 
*///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool start_string_delim_find(std::string line, char delimiter);

#endif