# Morphological Operations
The program `morphological_operations.cpp` will equalise/match images depending on the user's input.<br>

## Making the file using CMake (For MacOS)
Download the repository and clone it onto the device into a preferred directory using:<br>
`$ git clone https://github.com/jaybee-117/Image_Processing/tree/main/Morphological_operations`


Navigate into the `/Frequency_Filtering` directory and make the code using:<br>
`
$ cmake .
`
<br>
`
$ make
`

The `CMakeLists.txt` has been pre-configured assuming OpenCV has been made in `/opt/homebrew/Cellar/opencv/4.5.4_4`.
If OpenCV has been made into another folder find the `/lib/cmake/opencv4` subfolder of the installation directory and place it in `SET(OpenCV_DIR <../lib/cmake/opencv4>)` of `CMakeLists.txt`<br>
Run the executeable using:
`./Morphological_operations`

For easy usage, here's the code:
```
git clone https://github.com/jaybee-117/Image_Processing/tree/main/Morphological_operations
cd Morphological_operations
cmake .
make
./Morphological_operations
```