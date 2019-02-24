Joseph Michaud

To compile the program, do the following:

1. Extract Source.cpp to a folder of your choice
2. With Visual Studio 2015 installed, open the Developer Command Prompt for VS2015.
3. Use the cd command to go to the directory where Source.cpp is located
	Ex: "cd C:\Users\user\Documents\Program"
4. Enter the command "cl /O2 Source.cpp" to compile the file, creating Source.exe and Source.obj files in the same directory.
5. Run Source.exe by opening it.
6. As the program runs, the data will be printed to the screen. The data will also be saved into .csv files for insertion sort, heap sort, and quick sort. The n value and average execution time (in milliseconds) are saved for each n value and sorting algorithm. The maximum constant value of each algorithm is also displayed at the end.
