#include "ASMGenerator.h"

int main(void)
{
	std::fstream file("asm.asm", std::fstream::in | std::fstream::out | std::fstream::trunc);
	std::stringstream output;

	ASMBlock mainBlock;
	/*
		i = 0
		while (i < 10)
			i++
	*/
	mainBlock.Assign("i", 0);
	ASMBlock whileBlock;
	mainBlock.While("i", 10, BooleanOp::LessStrict, &whileBlock);
	whileBlock.AddAssign("i", "i", 1);

	mainBlock.GetASM(output);

	file << output.str();
	file.close();
}