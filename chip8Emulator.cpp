#include "chip8Emulator.hpp"
#include <chrono>
#include <cstdint>
#include <cstring>
#include <string>
#include <fstream> 
#include <vector>

constexpr uint16_t START_ADDRESS {0x200};
constexpr uint8_t FONTSET_START_ADDRESS {0x50}; 
constexpr uint8_t FONTSET_SIZE {80}; 
constexpr std::array<uint8_t, FONTSET_SIZE> fontSet {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
}; 

void Chip8::loadROM(const std::string& fileName) {
    // open file as stream of binary starting with the file pointer at the end
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);  

    if (file.is_open()) {
        // get size of file then allocate buffer to hold file contents
        std::streampos size {file.tellg()}; 
        std::vector<char> buffer(size);  

        // return back to begining of the file and fill buffer
        file.seekg(0, std::ios::beg); 
        file.read(buffer.data(), size); 
        file.close(); 

        // load ROM contents into the Chip8's memory, starting at 0x200
        for (uint16_t i {}; i < size; ++i)
            memory[START_ADDRESS + i] = buffer[i]; 
    }
}

Chip8::Chip8() : randGen(std::chrono::system_clock::now().time_since_epoch().count()) {
    // pc starts at 0x200
    pc = START_ADDRESS; 

    // load fonts into memory 
    for (uint8_t i {}; i < FONTSET_SIZE; i++) {
        memory[FONTSET_START_ADDRESS + i] = fontSet[i]; 
    }

    // initialize RNG
    randByte = std::uniform_int_distribution<uint8_t>(0, 255U); 
}

// clear display
void Chip8::OP_00E0() {
    std::memset(video.data(), 0, sizeof(video)); 
}

// return from subroutine
void Chip8::OP_00EE() {
    --sp; 
    pc = stack[sp]; 
}
