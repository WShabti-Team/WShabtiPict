#ifndef __CASE_TEST_GENERATOR_H__
#define __CASE_TEST_GENERATOR_H__

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Generates an output file containing all k-way combinatorial tests 
 * 
 * INPUT:
 * input_file with this format
 * 
 *      parameter_name1:value_p1_1,value_p1_2,value_p1_2,...
 *      parameter_name2:value_p2_1,value_p2_2,value_p2_3,...
 *      parameter_name3:value_p3_1,value_p3_2,value_p3_3,...
 *      ...
 *      #CONSTRAINTS
 *      value_p1_x,value_p2_x,value_p3_x,...
 *      value_p1_y,value_p2_y,value_p3_y,...
 * 
 *      CONSTRAINTS ARE SPECIFIED WITH ENUMERATION OF EXCLUDED VALUES. * MUST BE USED IF NO VALUE IS CHOSEN FOR A SPECIFIC PARAMETER
 *      e.g
 *      filesystem:ntfs,ext4,apfs
 *      clustersize:512,1024,2048
 *      computer:laptop
 *      #CONSTRAINTS
 *      ntfs,512,* -> will exclude combination (ntfs,512,laptop)
 *      ntfs,*,* -> will exclude ALL combination starting with ntfs (ntfs,512,laptop),(ntfs,1024,laptop),(ntfs,2048,laptop)
 *      *,1024,laptop -> will exclude (ntfs,1024,laptop),(ext4,1024,laptop),(apfs,2048,laptop)  
 * 
 *      TO SPECIFY NUMERIC INTERVALS YOU CAN ALSO USE START:STOP:STEP SYNTAX
 *      parameter_name:num_value_start:num_value_stop:num_value_step (e.g numbers:1:10:1,32,46,64)
 * 
 * OUTPUT:
 */ 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_generator(int k_degree, std::string input_file, std::string output_file);

#endif