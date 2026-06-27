#include <iostream>
#include <fstream>
#include <string>

template <typename T>
std::string VarToHex(T var) {
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


int line_width = 5;
int lines_visible = 5;
int scroll = 1;


int main(int argc, char** argv) {
	// If there is 1 argument then attempt to open the file
	if (argc == 2) {
		std::string file_contents = ReadFile(argv[1]);
		int line = (line_width*lines_visible);
		for (int i = (scroll-1)*line; i < scroll*line; i++) {
			if (i%line_width == 0) {
				std::cout << std::endl;
			}
			if (file_contents.size() > i) {
				char character = file_contents.c_str()[i];
				std::string hex_byte = VarToHex<char>(character);
				// If it is a null character, show it as red
				if (character == '\x00') {
					std::cout << "\e[38;2;255;0;0m";
				}


				std::cout << hex_byte << "\e[0m ";
			} else {
				// Make it show as gray
				std::cout << "\e[38;2;100;100;100m00\e[0m" << " ";
			}
		}

	}
	
	return 0;
	
}
