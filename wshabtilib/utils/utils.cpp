#include<string>
#include<vector>

using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------------

vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

int position_in_vector(vector<string> vect, string target)
{
    for(int i=0; i<vect.size(); i++)
    {
        if(vect[i].compare(target) == 0)
        {
            return i;
        }
    }
    return -1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

bool start_string_delim_find(string line, char delimiter)
{
	if(line[0] == delimiter)
		return true;
	else
		return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------