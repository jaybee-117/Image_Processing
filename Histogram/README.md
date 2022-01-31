# Histogram Matching & Equalisation
The program `Histogram_Equalisation_Matching.cpp` will equalise/match images depending on the user's input.

## Making the file using CMake (For Linux/Ubuntu/WSL)
Download the repository and clone it onto the device into a preferred directory using: <br>
`$ git clone https://github.com/jaybee-117/Image_Processsing/Histogram`<br>
Assuming the OpenCV library has been made using CMake in ~/opencv:
Navigate into the `/Histogram` directory and make the code using: <br>
```
cmake .
make
```
The `CMakeLists.txt` has been pre-configured by me, so you do not have to rewrite it.
If OpenCV has been made into another folder find the `/lib/cmake/opencv4` subfolder of the installation directory <br>and place it in `SET(OpenCV_DIR <../lib/cmake/opencv4>)` of `CMakeLists.txt`<br>
Run the executeable using:
`./Histogram_Equalisation_Matching`

For easy usage, here's the code:
```
git clone https://github.com/jaybee-117/Image_Processsing/Histogram`
cd Histogram
cmake .
make
./Histogram
```