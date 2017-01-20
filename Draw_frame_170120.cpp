//
// Writes a povray script to plot a frame
//
// Compilation: g++ Draw_frame_160527.cpp
// ./a.out n
// Where n is the number of frame we want to plot and extract.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using namespace std;


int main( int argc, const char* argv[] )
{
	if ( argc < 2 )
	{
		std::cout << BOLDRED << "\tATTENTION: WRONG USAGE!!!" << RESET << std::endl ;
		std::cout << BOLDRED << "\t./a.out [frame number]" << RESET << std::endl ;
		return (0) ;
	}

	// Line to detect
	std::string search_str = "Atoms. Timestep: " ; // String to find
	search_str += argv[1] ;
	std::cout << std::endl ;

	std::cout << " Frame to be plot and extracted: " << search_str << std::endl ;

	// Open trajectory file
	std::ifstream file( "traj_all.xyz" ) ;   // file where the extraction is performed
	std::string line ;                       // variable string to read the line
	int line_number = 0 ;                    // counter for lines
	int i;                                   // index for the loop
        
	// File where the extracted lines are print
	std::ofstream out_framexyz ;
	out_framexyz.open ("Extracted_frame.xyz", ios::out ); //| ios::app | ios::binary
        
	unsigned int Frame_counter = 0 ;
	double Rgas = 0.5 ;
	double Rliquid = 0.5 ;

	// Read number of atoms (first line)
	std::getline(file, line);
	int lines_2_read = atoi(line.c_str());
	std::cout << " Atoms detected: " << lines_2_read << std::endl ;
        

	// Plot and save the atoms of an specific frame
	while( std::getline( file, line ) )
	{
////		if ( line_number == 1 ) return(0) ;
		line_number++ ;
            
		if( line.find(search_str) != std::string::npos ) //npos
		{
			std::cout << "String matched at line: " << line_number << ". Full line is: " << line << std::endl ;

			unsigned int number_of_gas = 0 ;
			unsigned int number_of_liquid = 0 ;
			unsigned int number_of_atoms = 0 ;


			// Build a name for the different frames
			++Frame_counter ;       
                
			// File where the povray script for a specific frame is written 
			// http://stackoverflow.com/questions/11437702/inserting-int-variable-in-file-name 
			// http://stackoverflow.com/questions/26161072/inserting-int-into-file-name-using-stringstream
			std::ostringstream ss;
			ss << "frame_no_" << Frame_counter << ".pov";
			std::ofstream out_file;
			out_file.open(ss.str().c_str());
                
			// Header of the povray file
			out_file << "// Creating POV-RAY Script to render\n";
			out_file << "\n";
			out_file << "#include \"colors.inc\"\n";
			out_file << "#include \"textures.inc\"\n";
			out_file << "#include \"textures.inc\"\n";
			out_file << "\n";
			out_file << "background{White}\n";
			out_file << "camera { location <0,0,100> look_at <0,0,0> angle 0 rotate <0,0,clock*360>}\n";
			out_file << "light_source { <0, 100,0> color White }\n";
			out_file << "light_source { <0,-100,0> color White }\n";
			out_file << "light_source { < 100,0,0> color White }\n";
			out_file << "light_source { <-100,0,0> color White }\n";
			out_file << "light_source { <0,0, 100> color White }\n";
			out_file << "light_source { <0,0,-100> color White }\n";                                                               
                
			for (i=0; i<lines_2_read; i++)
			{
				++number_of_atoms ;
				unsigned int element ;
				double x, y, z ;
				std::getline(file, line) ;
				std::stringstream aa(line) ;
				aa >> element >> x >> y >> z ;

				// std::cout << "Read line: " << element << "   " << x << "    " << y << "    " << z  << std::endl ;
				if(element == 1)
				{
					++number_of_gas; // sums the number of gas atoms
					out_file << "// Atom number " <<  number_of_atoms << " Gas atom number " << number_of_gas  << std::endl ;
					out_file << "sphere { <" << x << "," << y << "," << z << ">," << Rgas << " pigment { rgbt <1,0,0,0>} finish { phong 0.7 phong_size 20 }}"  << std::endl ;
					out_framexyz << element << "   " << x << "    " << y << "    " << z << std::endl ;
				}
                    
				if(element == 2)
				{
					++number_of_liquid; // sums the number of gas atoms
					out_file << "// Atom number " <<  number_of_atoms << " Liquid atom number " << number_of_liquid  << std::endl ;
					out_file << "sphere { <" << x << "," << y << "," << z << ">," << Rliquid << " pigment { rgbt <0,0,1,0>} finish { phong 0.7 phong_size 20 }}" << std::endl ;
					out_framexyz << element << "   " << x << "    " << y << "    " << z << std::endl ;
				}
			}
			out_file.close();

//////			system("povray *.pov +A -D +W2400 +H1800");
//////			std::remove(ss.str().c_str()); 
		}
	}
	return (0) ;
}

//        std::cout << " POVRAY script povray.pov has been generated\n";
 //       std::cout << " You can now: povray povray.pov                     -> fast rendering\n";
  //      std::cout << "              povray povray.pov +A -D +W2400 +H1800 -> high quality rendering\n";
   //     std::cout << "              povray rotate.ini                     -> rotation sequence to generate a video\n";
