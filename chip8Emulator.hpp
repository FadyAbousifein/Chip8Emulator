#include <cstdint>
#include <array> 
#include <random>
#include <string>

constexpr uint8_t VIDEO_WIDTH {64}; 
constexpr uint8_t VIDEO_HEIGHT {32}; 
constexpr uint16_t VIDEO_DIMENSION {VIDEO_HEIGHT* VIDEO_WIDTH}; 

class Chip8 { public: 
        Chip8(); 
        void loadROM(const std::string& filename); 

        private:
            // Do nothing
            void OP_NULL();

            // CLS
            void OP_00E0();

            // RET
            void OP_00EE();

            // JP address
            void OP_1nnn();

            // CALL address
            void OP_2nnn();

            // SE Vx, byte
            void OP_3xkk();

            // SNE Vx, byte
            void OP_4xkk();

            // SE Vx, Vy
            void OP_5xy0();

            // LD Vx, byte
            void OP_6xkk();

            // ADD Vx, byte
            void OP_7xkk();

            // LD Vx, Vy
            void OP_8xy0();

            // OR Vx, Vy
            void OP_8xy1();

            // AND Vx, Vy
            void OP_8xy2();

            // XOR Vx, Vy
            void OP_8xy3();

            // ADD Vx, Vy
            void OP_8xy4();

            // SUB Vx, Vy
            void OP_8xy5();

            // SHR Vx
            void OP_8xy6();

            // SUBN Vx, Vy
            void OP_8xy7();

            // SHL Vx
            void OP_8xyE();

            // SNE Vx, Vy
            void OP_9xy0();

            // LD I, address
            void OP_Annn();

            // JP V0, address
            void OP_Bnnn();

            // RND Vx, byte
            void OP_Cxkk();

            // DRW Vx, Vy, height
            void OP_Dxyn();

            // SKP Vx
            void OP_Ex9E();

            // SKNP Vx
            void OP_ExA1();

            // LD Vx, DT
            void OP_Fx07();

            // LD Vx, K
            void OP_Fx0A();

            // LD DT, Vx
            void OP_Fx15();

            // LD ST, Vx
            void OP_Fx18();

            // ADD I, Vx
            void OP_Fx1E();

            // LD F, Vx
            void OP_Fx29();

            // LD B, Vx
            void OP_Fx33();

            // LD [I], Vx
            void OP_Fx55();

            // LD Vx, [I]
            void OP_Fx65();

            std::array<uint8_t, 16> registers           {};
            std::array<uint8_t, 4096>  memory           {}; 
            uint16_t index                              {}; 
            uint16_t pc                                 {}; 
            std::array<uint16_t, 16> stack              {}; 
            uint8_t sp                                  {}; 
            uint8_t delaytimer                          {}; 
            uint8_t soundtimer                          {}; 
            std::array<uint8_t, 16> keypad              {}; 
            std::array<uint32_t, VIDEO_DIMENSION> video {}; 
            uint16_t opcode                             {}; 

            std::default_random_engine randGen; 
            std::uniform_int_distribution<uint8_t> randByte; 
};
