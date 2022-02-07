# Spatial Filtering
The program `Histogram_Equalisation_Matching.cpp` will equalise/match images depending on the user's input.

## Making the file using CMake (For Linux/Ubuntu/WSL)
Download the repository and clone it onto the device into a preferred directory using:<br>
`$ git clone https://github.com/jaybee-117/Image_Processing/Spatial_Filtering`

Assuming the OpenCV library has been made using CMake in ~/opencv:
Navigate into the `/Spatial_Filtering` directory and make the code using:<br>
`
$ cmake .
`
<br>
`
$ make
`

The `CMakeLists.txt` has been pre-configured assuming OpenCV has been made in `~/opencv`.
If OpenCV has been made into another folder find the `/lib/cmake/opencv4` subfolder of the installation directory and place it in `SET(OpenCV_DIR <../lib/cmake/opencv4>)` of `CMakeLists.txt`<br>
Run the executeable using:
`./Spatial_Filtering`

For easy usage, here's the code:
```
git clone https://github.com/jaybee-117/Image_Processing/Spatial_Filtering
cd Spatial_Filtering
cmake .
make
./Spatial_Filtering
```