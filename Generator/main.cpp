#include "ASMGenerator.h"

#define SCREEN 0x4000
#define KEYBOARD 0x6000
#define ARROWUP 131
#define ARROWDOWN 133
#define ARROWRIGHT 132
#define ARROWLEFT 130

int main(void)
{
	std::fstream file("asm.asm", std::fstream::in | std::fstream::out | std::fstream::trunc);
	std::stringstream output;

	/*
		// box
		x = 16
		y = 8
		boxWidth = 1
		boxHeight = 1

		// invalidateRect
		invalidateX = 0
		invalidateY = 0
		inavlidateWidth = 0
		invalidateHeight = 0
		bInvalidateRect = true

		// constants
		const pKey = KEYBOARD
		const NegOne = -1

		// for sensitive key
		lastKey = 0
		thisKey = 0
		// timer = 0

		while (true) // gameLoop
			thisKey = *pKey
			if (thisKey != lastKey) // keyIf
				if (thisKey != 0) // keyIf2
					bInvalidateRect = true
					invalidateX = x
					invalidateY = y
					invalidateWidth = 1
					invalidateHeight = 1
					if (thisKey == arrowUp)
						if (y > 0)
							y--
					if (thisKey == arrowDown)
						if (y < 15)
							++
					if (thisKey == arrowRight)
						if (x < 31)
							x++
					if (thisKey == arrowLeft)
						if (x > 0)
							x--
				lastKey = thisKey

			if (bInvalidateRect) // invaldiateRectIf
				InvalidateRect(invalidateX, invalidateY, invalidateWidth, invalidteHeight)
				DrawGrid();
				DrawBox(x, y);
				bInvalidateRect = false

			// sleep(10)
	*/

	/*
		DrawBox(x, y, boxWidth, boxHeight)
		{
			pDrawBoxTemp = SCREEN + x + y * 512
			for (16) // drawBoxFor
				*pDrawBoxTemp = NegOne
				pDrawBoxTemp += 32
		}
	*/

	/*
		DrawGrid()
		{
			// columns
			screenEnd = 0
			addr = SCREEN
			while (screenEnd < 32) // whileBlock3
				while ( addr < KEYBOARD) // whileBlock4
					m[addr] |= 1
					addr += 32
				screenEnd += 1
				addr = SCREEN + screenEnd

			// rows
			screenEnd = SCREEN + 32
			addr = SCREEN
			while (screenEnd < KEYBOARD) // whileBlock1
				while (addr < screenEnd) // whileBlock2
					m[addr] = m[addr] | NegOne
					addr++
				addr += 32*15 (480)
				screenEnd += 32*16 (512)
		}
	*/

	/*
		InvalidateRect(invalidateX, invalidateY, invalidateWidth, invalidteHeight)
		{
			IRWidth = 0
			while (IRWidth < invalidateWidth) // IRWhile1
				IRHeight = 0
				while (IRHeight < invalidteHeight) // IRWhile2
					pIRAddr = SCREEN + invalidateX + invalidateY * 512
					for (16) // IRFor
						*pIRAddr = 0
						pIRAddr += 32
					invalidateX++
					IRHeight++
				IRWidth++
				invalidateY++
		}
	*/

	/*
		Sleep(clock)
		{
			while (timer < clock)
				timer++
			timer = 0
		}
	*/
	
	ASMBlock mainBlock;
	mainBlock.Assign("x", 16);
	mainBlock.Assign("y", 8);

	mainBlock.Assign("invalidateX", 0);
	mainBlock.Assign("invalidateY", 0);
	mainBlock.Assign("invalidateWidth", 0);
	mainBlock.Assign("invalidateHeight", 0);
	mainBlock.Assign("bInvalidateRect", 1);

	mainBlock.Assign("pKey", KEYBOARD);
	mainBlock.Assign("NegOne", 0);
	mainBlock.SubtractAssign("NegOne", "NegOne", 1);

	mainBlock.Assign("lastKey", 0);
	mainBlock.Assign("thisKey", 0);
	mainBlock.Assign("timer", 0);

	ASMBlock gameLoop;
	mainBlock.While("isGameOver", 0, BooleanOp::Equal, &gameLoop);

	ASMBlock keyIf, keyIf2, invalidateRectIf;
	gameLoop.Assign("thisKey", "*pKey");
	gameLoop.If("thisKey", "lastKey", BooleanOp::NotEqual, &keyIf);
	gameLoop.If("bInvalidateRect", 1, BooleanOp::Equal, &invalidateRectIf);
	
	//ASMBlock timerWhile;
	//gameLoop.While("timer", 1, BooleanOp::LessStrict, &timerWhile);
	//timerWhile.AddAssign("timer", "timer", 1);
	//gameLoop.Assign("timer", 0);

	keyIf.If("thisKey", 0, BooleanOp::NotEqual, &keyIf2);

	keyIf2.Assign("bInvalidateRect", 1);
	keyIf2.Assign("invalidateX", "x");
	keyIf2.Assign("invalidateY", "y");
	keyIf2.Assign("invalidateWidth", 1);
	keyIf2.Assign("invalidateHeight", 1);

	ASMBlock keyCondUp, keyCondDown, keyCondRight, keyCondLeft;
	keyIf2.If("thisKey", ARROWRIGHT, BooleanOp::Equal, &keyCondRight);
	keyIf2.If("thisKey", ARROWLEFT, BooleanOp::Equal, &keyCondLeft);
	keyIf2.If("thisKey", ARROWUP, BooleanOp::Equal, &keyCondUp);
	keyIf2.If("thisKey", ARROWDOWN, BooleanOp::Equal, &keyCondDown);
	keyIf.Assign("lastKey", "thisKey");

	ASMBlock keyCondUp1, keyCondDown1, keyCondRight1, keyCondLeft1;

	keyCondUp.If("y", 0, BooleanOp::GreaterStrict, &keyCondUp1);
	keyCondDown.If("y", 15, BooleanOp::LessStrict, &keyCondDown1);
	keyCondRight.If("x", 31, BooleanOp::LessStrict, &keyCondRight1);
	keyCondLeft.If("x", 0, BooleanOp::GreaterStrict, &keyCondLeft1);

	keyCondUp1.SubtractAssign("y", "y", 1);
	keyCondDown1.AddAssign("y", "y", 1);
	keyCondRight1.AddAssign("x", "x", 1);
	keyCondLeft1.SubtractAssign("x", "x", 1);

	ASMBlock whileBlock1, whileBlock2, whileBlock3, whileBlock4, drawBox;

	// InvalidateRect
	ASMBlock IRWhile1, IRWhile2, IRFor;
	invalidateRectIf.Assign("IRWidth", 0);
	invalidateRectIf.While("IRWidth", "invalidateWidth", BooleanOp::LessStrict, &IRWhile1);
	IRWhile1.Assign("IRHeight", 0);
	IRWhile1.While("IRHeight", "invalidateHeight", BooleanOp::LessStrict, &IRWhile2);
	IRWhile1.AddAssign("IRWidth", "IRWidth", 1);
	IRWhile1.AddAssign("invalidateY", "invalidateY", 1);

	IRWhile2.MultiplyAssign("pIRAddr", "invalidateY", 512);
	IRWhile2.AddAssign("pIRAddr", "pIRAddr", SCREEN);
	IRWhile2.AddAssign("pIRAddr", "pIRAddr", "invalidateX");
	IRWhile2.For(16, &IRFor);
	IRWhile2.AddAssign("invalidateX", "invalidateX", 1);
	IRWhile2.AddAssign("IRHeight", "IRHeight", 1);

	IRFor.Assign("*pIRAddr", 0);
	IRFor.AddAssign("pIRAddr", "pIRAddr", 32);


	// DrawGrid
	invalidateRectIf.Assign("screenEnd", 0);
	invalidateRectIf.Assign("addr", SCREEN);
	invalidateRectIf.While("screenEnd", 32, BooleanOp::LessStrict, &whileBlock3);
	whileBlock3.While("addr", KEYBOARD, BooleanOp::LessStrict, &whileBlock4);
	whileBlock4.BitwiseOrAssign("*addr", "*addr", 1);
	whileBlock4.AddAssign("addr", "addr", 32);
	whileBlock3.AddAssign("screenEnd", "screenEnd", 1);
	whileBlock3.AddAssign("addr", "screenEnd", SCREEN);

	invalidateRectIf.Assign("screenEnd", 0x4020);
	invalidateRectIf.Assign("addr", SCREEN);
	invalidateRectIf.While("screenEnd", KEYBOARD, BooleanOp::LessStrict, &whileBlock1);
	whileBlock1.While("addr", "screenEnd", BooleanOp::LessStrict, &whileBlock2);
	whileBlock2.BitwiseOrAssign("*addr", "*addr", "NegOne");
	whileBlock2.AddAssign("addr", "addr", 1);
	whileBlock1.AddAssign("addr", "addr", 480);
	whileBlock1.AddAssign("screenEnd", "screenEnd", 512);

	// DrawBox
	ASMBlock drawBoxFor;
	invalidateRectIf.MultiplyAssign("pDrawBoxTemp", "y", 512);
	invalidateRectIf.AddAssign("pDrawBoxTemp", "pDrawBoxTemp", SCREEN);
	invalidateRectIf.AddAssign("pDrawBoxTemp", "pDrawBoxTemp", "x");
	invalidateRectIf.For(16, &drawBoxFor);
	invalidateRectIf.Assign("bInvalidateRect", 0);

	drawBoxFor.Assign("*pDrawBoxTemp", "NegOne");
	drawBoxFor.AddAssign("pDrawBoxTemp", "pDrawBoxTemp", 32);

	mainBlock.GetASM(output);

	//ASMBlock testBlock, testFor;
	//testBlock.Assign("y", 8);
	//testBlock.MultiplyAssign("test", "y", 32);

	//testBlock.GetASM(output);

	file << output.str();
	file.close();
}