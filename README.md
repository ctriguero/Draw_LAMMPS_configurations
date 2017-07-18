# Draw_LAMMPS_configurations
# (1) Package description & content:

**(1.1)** **Description**: The package contains a series of programs useful to *represent configurations* or *create videos* given an *xyz* file via [POVRAY](http://www.povray.org/) to render the images and [FFmpeg](https://ffmpeg.org/) to render the videos. For this reason a prerequsite to use this programs is to have [POVRAY](http://www.povray.org/) and [FFmpeg](https://ffmpeg.org/) installed. Depending on the version or type of *xyz* file the programs may need some small adaptation.

**(1.2)** **Content**:

- A program to visualize selected frames in a whole *xyz* trajectory:

**Draw_frame_160527.cpp**

- A program to visualize all the frames in a whole *xyz* trajectory and render a video:

**Video_from_trajectory.cpp**

# (2) Usage

**(2.1)** **Compilation**:

- g++ [program name.cpp]

**(2.2)** **Running the program**:
