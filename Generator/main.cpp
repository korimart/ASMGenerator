#include "ASMGenerator.h"

#define SCREEN 0x4000
#define KEYBOARD 0x6000

int main(void)
{
	std::fstream file("asm.asm", std::fstream::in | std::fstream::out | std::fstream::trunc);
	std::stringstream output;

	/*
		// columns
		const NegOne = -1
		screenEnd = 0
		addr = SCREEN
		while (screenEnd < 32)
			while ( addr < KEYBOARD)
				m[addr] = m[addr] | 1
				addr += 32
			screenEnd += 1
			addr = SCREEN + screenEnd

		// rows
		screenEnd = SCREEN + 32
		addr = SCREEN
		while (screenEnd < KEYBOARD)
			while (addr < screenEnd)
				m[addr] = m[addr] | NegOne
				addr++
			addr += 32*15 (480)
			screenEnd += 32*16 (512)
	*/

	ASMBlock mainBlock, whileBlock1, whileBlock2, whileBlock3, whileBlock4;
	mainBlock.Assign("screenEnd", 0);
	mainBlock.Assign("addr", SCREEN);
	mainBlock.While("screenEnd", 32, BooleanOp::LessStrict, &whileBlock3);
	whileBlock3.While("addr", KEYBOARD, BooleanOp::LessEqual, &whileBlock4);
	whileBlock4.AssignAtAddress("addr", 1);
	whileBlock4.AddAssign("addr", "addr", 32);
	whileBlock3.AddAssign("screenEnd", "screenEnd", 1);
	whileBlock3.AddAssign("addr", "screenEnd", SCREEN);

	mainBlock.Assign("screenEnd", 0x4020);
	mainBlock.Assign("addr", SCREEN);
	mainBlock.While("screenEnd", KEYBOARD, BooleanOp::LessStrict, &whileBlock1);
	whileBlock1.While("addr", "screenEnd", BooleanOp::LessStrict, &whileBlock2);
	whileBlock2.AssignAtAddress("addr", 0x5555);
	whileBlock2.AddAssign("addr", "addr", 1);
	whileBlock1.AddAssign("addr", "addr", 480);
	whileBlock1.AddAssign("screenEnd", "screenEnd", 512);

	mainBlock.GetASM(output);

	file << output.str();
	file.close();
}