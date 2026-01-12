#include <cstdint>
#include <array> 
#include <string>

constexpr uint8_t VIDEO_WIDTH {64}; 
constexpr uint8_t VIDEO_HEIGHT {32}; 
constexpr uint16_t VIDEO_DIMENSION {VIDEO_HEIGHT* VIDEO_WIDTH}; 

class Chip8 { public: 
        Chip8(); 
        void loadROM(const std::string& filename); 

        std::array<uint8_t, 16> registers          {};
        std::array<uint8_t, 4096>  memory          {}; 
        uint16_t index                             {}; 
        uint16_t pc                                {}; 
        std::array<uint16_t, 16> stack             {}; 
        uint8_t sp                                 {}; 
        uint8_t delaytimer                         {}; 
        uint8_t soundtimer                         {}; 
        std::array<uint8_t, 16> keypad             {}; 
        std::array<uint32_t, VIDEO_DIMENSION> video {}; 
        uint16_t opcode                            {}; 


};
