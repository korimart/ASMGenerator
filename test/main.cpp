#include "..//Generator/ASMGenerator.h"

int main(void)
{
	std::fstream file("test.asm", std::fstream::in | std::fstream::out | std::fstream::trunc);
	std::stringstream output;

	ASMBlock mainBlock;

	RECT rt;
	rt.x = 15;
	rt.y = 8;
	rt.width = 2;
	rt.height = 2;

	mainBlock.Init();
	mainBlock.DrawImage("sample_image.txt", rt);
	mainBlock.GetASM(output);

	file << output.str();
	file.close();
}