//
// Writes a povray script to plot a frame
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <time.h>

using namespace std;


int main()
{
        std::ifstream file( "K.xyz" ) ; // file where the extraction is performed
        std::string search_str = "B" ; // String to find
        std::string line ;    // variable string to read the line
        int line_number = 0 ; // counter for lines
        int i;                // index for the loop
		int j;                // index for the loop
		int xx;
		int yy;
    
        double Rgas = 0.5 ;
        double Rliquid = 0.5 ;	
        
        std::cout << "\n" ;
        std::cout << "\n" ;
       
      //Read number of atoms (first line)
        std::getline(file, line);
        int lines_2_read = atoi(line.c_str());
        std::cout << lines_2_read << " atoms detected.\n";
        
        std::vector<double> vx(lines_2_read,0);
		std::vector<double> vy(lines_2_read,0);
		std::vector<double> vz(lines_2_read,0);
		std::vector<int> el(lines_2_read,0);
		
		std::vector<int> II(100,0);
		std::vector<int> JJ(100,0);
		
		//defining matrix
		std::vector< std::vector<int> > ADJ; 
		ADJ.resize(12);
		for (unsigned  i=0 ; i<12; ++i) ADJ[i].resize(12,0);
        
        ADJ[1][2]=1;
        
        ADJ[1][3]=1;
        ADJ[1][3]=1;
        ADJ[1][4]=1;
        ADJ[2][1]=1;
        ADJ[2][3]=1;
        ADJ[2][4]=1;
        ADJ[3][1]=1;
        ADJ[3][2]=1;
        ADJ[3][4]=1;
        ADJ[4][1]=1;
        ADJ[4][2]=1;
        ADJ[4][3]=1;
        
        
        ADJ[5][6]=1;
        ADJ[5][7]=1;
        ADJ[5][8]=1;
        ADJ[5][9]=1;
        ADJ[5][10]=1;
        ADJ[5][11]=1;
        
        ADJ[6][5]=1;
        ADJ[6][7]=1;
        ADJ[6][8]=1;
        ADJ[6][9]=1;
        ADJ[6][10]=1;
        ADJ[6][11]=1;
        
        ADJ[7][5]=1;
        ADJ[7][6]=1;
        ADJ[7][8]=1;
        ADJ[7][9]=1;
        ADJ[7][10]=1;
        ADJ[7][11]=1;
        
        ADJ[8][5]=1;
        ADJ[8][6]=1;
        ADJ[8][7]=1;
        ADJ[8][9]=1;
        ADJ[8][10]=1;
        ADJ[8][11]=1;
        
        ADJ[9][5]=1;
        ADJ[9][6]=1;
        ADJ[9][7]=1;
        ADJ[9][8]=1;
        ADJ[9][10]=1;
        ADJ[9][11]=1;
    
        ADJ[10][5]=1;
        ADJ[10][6]=1;
        ADJ[10][7]=1;
        ADJ[10][8]=1;
        ADJ[10][9]=1;
        ADJ[10][11]=1;
        
    	ADJ[11][5]=1;
        ADJ[11][6]=1;
        ADJ[11][7]=1;
        ADJ[11][8]=1;
        ADJ[11][9]=1;
        ADJ[11][10]=1;
   
        
        
        
        
        
        
        
        
        while( std::getline( file, line ) )
		{
			++line_number ;
            
			if( line.find(search_str) != std::string::npos )
            {
                std::cout << "String matched at line: " << line_number << ". Full line is: " << line << '\n' ;

                unsigned int number_of_gas = 0 ;
                unsigned int number_of_liquid = 0 ;
                
     
				for (i=0; i<lines_2_read; i++)
				{
					unsigned int element;
					double x, y, z;
			    	std::getline(file, line);  //Define a vector and store
			    	std::stringstream aa(line);
			    	aa >> element >> x >> y >> z;
			    	vx[i] = x ;
					vy[i] = y ;
					vz[i] = z ;
					el[i]=element ;		
				}
                         

				
   		          
   		        unsigned int Frame_counter=0 ;
   		        
   		        unsigned int counter2=0;
   		        
   		     	for (i=0; i<lines_2_read-1; i++)
				{
					
   		         	for (j=i+1; j<lines_2_read; j++)
   		          	{
   		          		//std::cout <<"j=  " << j << endl ;
   		          		if( (el[i] == 1) && (el[j] == 1) )
   		          		{
   		          		
   		          			
                            
            				//NAMES BEGIN Build a name for the different frames
                			Frame_counter++ ; 
                			//std::cout << "Frame= " << Frame_counter << endl;  
                			    
                			std::ostringstream ss;
                			std::ofstream out_file;
							if ( Frame_counter <= 9)
							{
							    ss << "frame_no_000" << Frame_counter << ".pov";
								out_file.open(ss.str().c_str(), std::fstream::trunc);
							}

							if ( (Frame_counter > 9) && (Frame_counter <= 99))
							{
							    ss << "frame_no_00" << Frame_counter << ".pov";
      			     	     	out_file.open(ss.str().c_str(), std::fstream::trunc);
							}

							if ( (Frame_counter > 99) && (Frame_counter <= 999))
							{
							    ss << "frame_no_0" << Frame_counter << ".pov";
								out_file.open(ss.str().c_str(), std::fstream::trunc);
							}
	
							if ( (Frame_counter > 999) && (Frame_counter <= 9999))
							{
						    	ss << "frame_no_" << Frame_counter << ".pov";
								out_file.open(ss.str().c_str(), std::fstream::trunc);
							}

		
							// Header of the povray file
							out_file << "// Creating POV-RAY Script to render\n";
							out_file << "\n";
							out_file << "#include \"colors.inc\"\n";
							out_file << "#include \"textures.inc\"\n";
							out_file << "#include \"textures.inc\"\n";
							out_file << "\n";
							out_file << "background{White}\n";
							out_file << "camera { up <0,1,0> right <1,0,0> location <0.0,0.0,20.0> look_at <0,0,0> angle 0 rotate <0,clock*360,0>}\n";
  					        out_file << "light_source { <0,0, 100> color White }\n";
  		   				   //NAMES END
   		          		
   		          			//std::cout << el[i] << "  "<< el[j] << "  " << i << "  " << j << endl;
   		          			out_file << "// Cylinder " << endl ;
   		          			out_file << "cylinder { <" << vx[i] << "," << vy[i] << "," << vz[i] << ">, <" << vx[j] << "," << vy[j] << "," << vz[j] << ">, " << Rliquid << " pigment { rgbt <1,1,0,0.5>} finish { phong 0.7 phong_size 20 }}\n";
   		          			//
   		          			//
   		          			//
   		          			unsigned int number_of_atoms=0;
   		          			for (int k=0; k<lines_2_read; k++)
							{
								++number_of_atoms;
								if(el[k] == 1)
								{
									++number_of_gas; // sums the number of gas atoms
									out_file << "// Atom number " <<  number_of_atoms << " Gas atom number " << number_of_gas << "\n";
									out_file << "sphere { <" << vx[k] << "," << vy[k] << "," << vz[k] << ">," << Rgas << " pigment { rgbt <0,0,1,0>} finish { phong 0.7 phong_size 20 }}\n"; 
								}
                    
								if(el[k] == 2)
								{
									++number_of_liquid; // sums the number of liquid
	                    			out_file << "// Atom number " <<  number_of_atoms << " Liquid atom number " << number_of_liquid << "\n";
									out_file << "sphere { <" << vx[k] << "," << vy[k] << "," << vz[k] << ">," << Rliquid << " pigment { rgbt <1,0,0,0>} finish { phong 0.7 phong_size 20 }}\n";	
					
   		            			}
   		          			}
   		          			
   		          			
   		          			
   		          			for (int kd=0; kd<counter2; kd++)
							{
								xx = II[kd];
								yy = JJ[kd];
							
								std::cout << " INDEX= " << counter2 <<"  " << xx << "  "<< yy << endl;
								out_file << "// Connector " << endl ;
   		          				out_file << "cylinder { <" << vx[xx] << "," << vy[xx] << "," << vz[xx] << ">, <" << vx[yy] << "," << vy[yy] << "," << vz[yy] << ">, " << "0.1" << " pigment { rgbt <0,0,1,0.0>} finish { phong 0.7 phong_size 20 }}\n";
							}
   		          			//
   		          			//
   		          			//
   		          			// http://www.povray.org/documentation/view/3.6.0/217/
							//	       system("povray *.pov +A -D +W2400 +H1800") ; // HD
						
							
	       					//system("povray *.pov +A Quality=7") ; // Intermediate
	       					//system("povray *.pov") ; // Basic quality
	       					out_file.close();
	       					
						    system("povray *.pov +A -D +W1000 +H1000") ; // HD
						
   		          			std::remove(ss.str().c_str()); 
   		          			
   		          			
   		          			
   		          			
   		          			
   		          			
   		          			// Connected part
   		          			
   		          			
   		          			
   		          			//NAMES BEGIN Build a name for the different frames
                			Frame_counter++ ; 
                			//std::cout << "Frame= " << Frame_counter << endl;  
                			    
                			ss.str("");
                            ss.clear(); // Clear state flags.
                			//std::ostringstream ss;
                			//std::ofstream out_file;
							if ( Frame_counter <= 9)
							{
							    ss << "frame_no_000" << Frame_counter << ".pov";
								out_file.open(ss.str().c_str(), std::fstream::trunc);
							}

							if ( (Frame_counter > 9) && (Frame_counter <= 99))
							{
							    ss << "frame_no_00" << Frame_counter << ".pov";
      			     	     	out_file.open(ss.str().c_str(), std::fstream::trunc);
							}

							if ( (Frame_counter > 99) && (Frame_counter <= 999))
							{
							    ss << "frame_no_0" << Frame_counter << ".pov";
								out_file.open(ss.str().c_str(), std::fstream::trunc);
							}
	
							if ( (Frame_counter > 999) && (Frame_counter <= 9999))
							{
						    	ss << "frame_no_" << Frame_counter << ".pov";
								out_file.open(ss.str().c_str(), std::fstream::trunc);
							}

		
							// Header of the povray file
							out_file << "// Creating POV-RAY Script to render\n";
							out_file << "\n";
							out_file << "#include \"colors.inc\"\n";
							out_file << "#include \"textures.inc\"\n";
							out_file << "#include \"textures.inc\"\n";
							out_file << "\n";
							out_file << "background{White}\n";
							out_file << "camera { up <0,1,0> right <1,0,0> location <0.0,0.0,20.0> look_at <0,0,0> angle 0 rotate <0,clock*360,0>}\n";
  					        out_file << "light_source { <0,0, 100> color White }\n";
  		   				   //NAMES END
   		          			
   		          		   //BEGIN All atoms
   		          		   
   		          		   
   		          		   
   		          		   
   		          		   number_of_atoms=0;
   		          			for (int k=0; k<lines_2_read; k++)
							{
								++number_of_atoms;
								if(el[k] == 1)
								{
									++number_of_gas; // sums the number of gas atoms
									out_file << "// Atom number " <<  number_of_atoms << " Gas atom number " << number_of_gas << "\n";
									out_file << "sphere { <" << vx[k] << "," << vy[k] << "," << vz[k] << ">," << Rgas << " pigment { rgbt <0,0,1,0>} finish { phong 0.7 phong_size 20 }}\n"; 
								}
                    
								if(el[k] == 2)
								{
									++number_of_liquid; // sums the number of liquid
	                    			out_file << "// Atom number " <<  number_of_atoms << " Liquid atom number " << number_of_liquid << "\n";
									out_file << "sphere { <" << vx[k] << "," << vy[k] << "," << vz[k] << ">," << Rliquid << " pigment { rgbt <1,0,0,0>} finish { phong 0.7 phong_size 20 }}\n";	
					
   		            			}
   		          			}
   		          			
   		          			//END All atoms
   		          			
   		          			//Set connections reading Adjmat 
   		          			
   		          			
   		          			
   		          			
   		          			if ( ADJ[i][j] == 1 )
   		          			{
   		          				//std::cout << " ADJ " << ADJ[i][j] << endl;
   		          				II[counter2] = i;
   		          				JJ[counter2] = j;
   		          				counter2++;
   		          			}
   		          			
   		          			std::cout << " pree loop" << endl;
   		          			// povray file for connector with atoms
   		          			for (int kd=0; kd<counter2; kd++)
							{
								xx = II[kd];
								yy = JJ[kd];
							
								std::cout << " INDEX= " << counter2 <<"  " << xx << "  "<< yy << endl;
								out_file << "// Connector " << endl ;
   		          				out_file << "cylinder { <" << vx[xx] << "," << vy[xx] << "," << vz[xx] << ">, <" << vx[yy] << "," << vy[yy] << "," << vz[yy] << ">, " << "0.1" << " pigment { rgbt <0,0,1,0.0>} finish { phong 0.7 phong_size 20 }}\n";
							}
							
							
							// output frame
							out_file.close();
	       					
						    system("povray *.pov +A -D +W1000 +H1000") ; // HD
						
   		          			std::remove(ss.str().c_str()); 
   		          			
   		          			
   		          			
   		          		}
   		          		
   		          		
   		          		
   		          		
   		          	}
				}
   		          
   		          
   		          
	       			
	       
			
					
			
		}
		
	}
	//system("ffmpeg -i frame_no_%04d.png -c:v libx264 -t 30 -pix_fmt yuv420p out.mp4") ; build video
	//system("ffmpeg -i out.mp4 -filter:v "setpts=6.0*PTS" slow.mp4"); slow down
	return (0) ;
}
