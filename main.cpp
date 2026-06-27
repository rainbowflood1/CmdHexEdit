#include <iostream>
#include <fstream>
#include <string>
// Define ansi escape codes so that you can use it to change the color of the text
#define NUM_LINE_OR_COL_COLOR "\e[38;2;255;255;0m"
#define RESET_COLOR "\e[0m"
#define NULL_BYTE_COLOR "\e[38;2;255;0;0m"
#define END_OF_FILE_COLOR "\e[38;2;100;100;100m"



// Both Windows and linux uses the same function to run terminal commands (this will be used to clear the terminal before placing the editor)
#ifdef __WIN__
#include <Windows.h>
#define CLEAR_CMD "cls"
#else
#include <unistd.h>
#define CLEAR_CMD "clear"
#endif


template <typename T>
std::string ToHex(T var) {
	std::string hex_code = std::format("{:X}", var);

	// If there is one hex character add a 0 before that hex character
	if (hex_code.size() == 1) {
		hex_code = "0" + hex_code;
	}

	return hex_code;
}

std::string ReadFile(std::string filename) {
	std::ifstream file(filename);
	std::string file_contents = "";
	std::string line;

	// Read the file
	
	while (std::getline(file, line)) {
		file_contents = file_contents + line;
	}

	file.close();

	return file_contents;
}


int line_width = 50;
int lines_visible = 25;
int scroll = 1;


int main(int argc, char** argv) {
	// If there is 1 argument then attempt to open the file
	if (argc == 2) {
		system(CLEAR_CMD);
		std::string file_contents = ReadFile(argv[1]);
		int lines_length = (line_width*lines_visible);
		int line_number = 0;
		// There is a "00: " so add a bunch of spaces to make it so that it is aligned with the hex code below
		std::cout << "    ";
		for (int i = 0; i < line_width; i++) {
			std::cout << NUM_LINE_OR_COL_COLOR << ToHex<int>(i) << RESET_COLOR << " ";
		}
		for (int i = (scroll-1)*lines_length; i < scroll*lines_length; i++) {
			if (i%line_width == 0) {
				std::cout << std::endl << NUM_LINE_OR_COL_COLOR << ToHex<int>(line_number) << ": " << RESET_COLOR;
				line_number++;

			}
			if (file_contents.size() > i) {
				char character = file_contents.c_str()[i];
				std::string hex_byte = ToHex<char>(character);
				// If it is a null character, show it as red
				if (character == '\x00') {
					std::cout << NULL_BYTE_COLOR;
				}


				std::cout << hex_byte << RESET_COLOR << " ";
			} else {
				// Make it show as gray
				std::cout << END_OF_FILE_COLOR << "00" << RESET_COLOR << " ";
			}
		}

	}
	
	return 0;
	
}
