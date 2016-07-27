//
// This program produces a video from a xyz trajectory of LAMMPS
//
// Carles Trigureo 2016
// 
// Version: 160613
// 
// (1) Recognition of each frame
// (2) Writes a povray script
// (3) Renders the script
// (4) Generates a video
//
// Requires having povray installed and running from shell
//
// This is designed for only two types of atoms but can be easily extended adding 
// more atom types and colors associated (see if (element == 1) part of the code)

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;


 int main()
    {
        std::ifstream file( "traj_all.xyz" ) ; // file where the extraction is performed
        std::string search_str = "imestep:" ; // String to find
        std::string line ;    // variable string to read the line
        int line_number = 0 ; // counter for lines
        int i;                // index for the loop
	    //int lines_2_read = 12672 ; // Number of lines to be extracted after we find search_str
        
        unsigned int Frame_counter = 0 ;
    
        double Rgas = 2.5 ;
        double Rliquid = 1.7 ;	
        
        std::cout << "\n" ;
        std::cout << "\n" ;
       
      //Read number of atoms (first line)
        std::getline(file, line);
        int lines_2_read = atoi(line.c_str());
        std::cout << lines_2_read << " atoms detected.\n";
        
        while( std::getline( file, line ) )
        {
            ++line_number ;
            
            if( line.find(search_str) != std::string::npos )
            {
                std::cout << "String matched at line: " << line_number << ". Full line is: " << line << '\n' ;

                unsigned int number_of_gas = 0 ;
                unsigned int number_of_liquid = 0 ;
                unsigned int number_of_atoms = 0 ;

	         // Build a name for the different frames
                ++Frame_counter ;       
                
             // File where the povray script for a specific frame is written 
             // http://stackoverflow.com/questions/11437702/inserting-int-variable-in-file-name 
             // http://stackoverflow.com/questions/26161072/inserting-int-into-file-name-using-stringstream
                std::ostringstream ss;
                std::ofstream out_file;
                
		        if ( Frame_counter <= 9)
	        	{
		            ss << "frame_no_000" << Frame_counter << ".pov";
                    out_file.open(ss.str().c_str());
		        }

		        if ( (Frame_counter > 9) && (Frame_counter <= 99))
		        {
		            ss << "frame_no_00" << Frame_counter << ".pov";
                    out_file.open(ss.str().c_str());
		        }

		        if ( (Frame_counter > 99) && (Frame_counter <= 999))
		        {
		            ss << "frame_no_0" << Frame_counter << ".pov";
                    out_file.open(ss.str().c_str());
		        }

		        if ( (Frame_counter > 999) && (Frame_counter <= 9999))
		        {
		            ss << "frame_no_" << Frame_counter << ".pov";
                    out_file.open(ss.str().c_str());
		        }
		
             // Header of the povray file
                out_file << "// Creating POV-RAY Script to render\n";
                out_file << "\n";
                out_file << "#include \"colors.inc\"\n";
                out_file << "#include \"textures.inc\"\n";
                out_file << "#include \"textures.inc\"\n";
                out_file << "\n";
                out_file << "background{White}\n";
                out_file << "camera { up <0,1,0> right <1,0,0> location <0.0,0.0,200.0> look_at <0,0,0> angle 0 rotate <0,clock*360,0>}\n";
                out_file << "light_source { <0, 100,0> color White }\n";
                out_file << "light_source { <0,-100,0> color White }\n";
                out_file << "light_source { < 100,0,0> color White }\n";
                out_file << "light_source { <-100,0,0> color White }\n";
                out_file << "light_source { <0,0, 100> color White }\n";
                out_file << "light_source { <0,0,-100> color White }\n";                                                               
                
                for (i=0; i<lines_2_read; i++)
                {
                    ++number_of_atoms;
                   
                 // THIS PART BROKE BEFORE ADDING STRINGSTREAM
                    unsigned int element;
                    double x, y, z;
		            std::getline(file, line);
		            std::stringstream aa(line);
		            aa >> element >> x >> y >> z;
                
    	    
                    //std::cout << "Read line: " << element << "   " << x << "    " << y << "    " << z <<'\n';
        		    if(element == 1)
                    {
                        ++number_of_gas; // sums the number of gas atoms
                        out_file << "// Atom number " <<  number_of_atoms << " Gas atom number " << number_of_gas << "\n";
                        out_file << "sphere { <" << x << "," << y << "," << z << ">," << Rgas << " pigment { rgbt <0,0,1,0>} finish { phong 0.7 phong_size 20 }}\n";
                    }
                    
                    if(element == 2)
                    {
                        ++number_of_liquid; // sums the number of gas atoms
                        out_file << "// Atom number " <<  number_of_atoms << " Liquid atom number " << number_of_liquid << "\n";
                        out_file << "sphere { <" << x << "," << y << "," << z << ">," << Rliquid << " pigment { rgbt <1,0,0,0>} finish { phong 0.7 phong_size 20 }}\n";
                    }
	       }
	       out_file.close();
	       
	       // http://www.povray.org/documentation/view/3.6.0/217/
	       //system("povray *.pov +A -D +W2400 +H1800") ; // HD
	       system("povray *.pov +A Quality=7 +W1000 +H1000") ; // Intermediate
	       //system("povray frame_no_*.pov +W1000 +H1000") ; // Basic quality
	       std::remove(ss.str().c_str()); 
           }
     }
	file.close();
	system("ffmpeg -i frame_no_%04d.png -c:v libx264 -t 30 -pix_fmt yuv420p out.mp4") ;
        return (0) ;
//        std::cout << " POVRAY script povray.pov has been generated\n";
 //       std::cout << " You can now: povray povray.pov                     -> fast rendering\n";
  //      std::cout << "              povray povray.pov +A -D +W2400 +H1800 -> high quality rendering\n";
   //     std::cout << "              povray rotate.ini                     -> rotation sequence to generate a video\n";
    }
