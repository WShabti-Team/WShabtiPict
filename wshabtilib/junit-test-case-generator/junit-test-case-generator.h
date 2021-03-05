#ifndef __JUNIT_TEST_CASE_GENERATOR_H__
#define __JUNIT_TEST_CASE_GENERATOR_H__


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Generates Test Class (it will add Test to test_class_name)
 * e.g Dog -> TestDog.java
 * INPUT:
 *      input_file_path : path of SOURCE CODE file
 *      output_file_path : path of .java test class file
 *      class_name : name of the test class (it will add Test as prefix)
 *      prototypes : string vector of prototypes for which test cases must be generated
 * 
 * OUTPUT:
 *      
 */     
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_source_code_generate(std::string input_file_path, std::string output_file_path, std::string test_class_name, std::vector<std::string> prototypes);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/* This method generetes a @ParameterizedTest (Junit5) for a method_prototype (returning it as a string)
 * 
 * INPUT:
 *      file path (used only for delta_check)    
 *      method prototype
 *      class name (because method must be called from a class/object)
 * 
 * OUTPUT:
 *      string of the @ParameterizedTest
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string method_test_case_generate(std::string input_file_path, std::string method_prototype, std::string class_name);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Takes a function prototype, adds oracle parameter input to function prototype according to the situation (based on bool input)
 *      (e.g int sum(int a, int b) -> int sum(int a, int b, Object oracle) (if interval_found is FALSE)
 *                                 -> int sum(int a, int b, double oracle, double delta) (if interval_found is TRUE)
 * 
 * INPUT:
 *      string of function prototype
 *      bool of interval found (true if at least one row contains an interval expression such as 1.5:0.1)
 * OUTPUT:
 *      string of function prototype with oracle added as parameter
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string add_oracle_to_arguments(std::string prototype, bool interval_found);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Takes a csv file path and checks if (every, because all rows contain the same number of values) row contains more than num_of_parameters parameters 
 * Indeed, delta range is added to the number of parameters
 *  
 * INPUT:
 *      CSV file path
 * 
 * OUTPUT:
 *      True (False): number of parameters per row is NOT equal (equal) to num_of_parameters
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool delta_check(std::string input_file_path, int num_of_parameters);

#endif