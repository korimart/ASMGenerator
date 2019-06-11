# ASMGenerator
nand2tetris.org의 CPU emulator 프로그램에서 쓰이는 기계언어를 감싸는 wrapper functions 이며 서울시립대학교 논리회로및실습 수업의 과제 제출용으로 제작되었습니다. 

Generator 프로젝트 내부에는 본 wrapper functions의 header file 및 cpp file 이외에도 과제제출용 asm.asm 파일 및 그 제작에 사용된 main.cpp 파일이 동봉되어 있으니 참고하시기 바랍니다.

# Usage
먼저 ASMGenerator.h를 include한 후 ASMBlock 클래스의 객체를 생성하고 초기화합니다.

    #include "ASMGenerator.h"
    ASMBlock mainBlock;
    mainBlock.init();

ASMBlock은 C언어에서 {로 시작하여 }로 끝나는 하나의 Block (compound statements)를 나타내는 객체입니다. 가장 바깥 Block을 생성하는 것은 C언어에서 main 함수 Block을 만드는 것과 비슷합니다. 가장 바깥 ASMBlock은 사용전에 항상 ASMBlock::init() 함수를 호출해야 합니다.

다음은 변수를 선언하고 초기화하는 예시입니다.

    mainBlock.Assign("x", 3); // x = 3
    mainBlock.Assign("x", "b"); // x = b
    mainBlock.Assign("x", "*foo"); // x = *foo

변수이름은 std::string 객체로 나타내어지며 첫 사용시 메모리에 전역변수로 할당됩니다. 모든 변수는 전역변수로만 선언됩니다. 즉, ASMBlock 내에서 처음 사용하였다고 하더라도 지역변수가 아닌 전역변수이며 ASMBlock의 종료 시 소멸하지 않습니다. 이는 구현의 간단함을 위해 Stack을 구현하지 않았기 때문이며 같은 이유로 모든 함수는 inline으로 처리됩니다.

두번째 인자로 uint16_t 값을 줄때에는 A 레지스터의 특성상 15비트 양수만 넘길 수 있습니다. 본 wrapper는 음수를 염두에 두고 작성되지 않았으므로 음수와 관련된 연산은 일절해서는 안 됩니다.

변수이름에는 모든 조합을 허용하되 "\*" 또는 "__tempKorimart" + 숫자 로 시작할 수 없습니다. "\*"는 변수이름의 앞에 붙여 변수를 포인터로 취급할 때 사용합니다. 위 예시의 첫번째 줄에서 변수 x에는 3이 들어간 상태이며 함수의 인자로 "*x"를 넘기면 메모리주소 3에 위치한 값을 넘기게 됩니다. 후자는 이름 없는 변수에 사용됩니다.(아래 설명)

비슷한 함수들로는 다음이 있습니다.

    mainBlock.AddAssign("a", "b", "1"); // a = b + 1;
    mainBlock.SubtractAssign("a", "b", "c"); // a = b - c;
    mainBlock.MultiplyAssign("a", "*b", 10); // a = *b * 10; (b가 가리키는 값)
    mainBlock.BitwiseAndAssign("*a", "b", 133); // *a = b & 133; (a가 가리키는 값)
    mainBlock.BitwiseOrAssign("*a", "*b", "*c"); // *a = *b | *c (a, b, c가 가리키는 값)
이들 함수는 첫번째 인자로 저장될 변수의 이름(std::string), 두번째 인자로 왼쪽 피연산자(std::string)), 세 번째 인자로 오른쪽 피연산자(uint16_t 또는 std::string)을 받습니다. 
 - a = 2 + 3 과 같은 컴파일타임  연산을 회피하기 위하여 두번째 인자는 반드시 변수의 이름을 넘겨받습니다. 상수끼리의 덧셈은 계산기를 이용하십시오.
 - 사칙연산 또는 비트연산의 결과는 반드시 어딘가에 저장되어야 합니다. 이는 temporary value의 구현을 피하기 위한 조치입니다.
 - 다시 한번 말하지만 음수의 연산을 해서는 안 됩니다. SubtractAssign의 경우 0에서 뺌으로써 메모리에 음수를 저장하는 것이 가능하지만 음수가 저장된 변수를 함수의 인자로 넘기지 마세요.

다음은 사용가능한 나머지 Statement 입니다.

    ASMBlock whileBlock, ifBlock, forBlock;
    
    // while (a < b) { /* -- while block -- */ }
    mainBlock.While("a", "b", BooleanOp::LessStrict, &whileBlock);
    
    // if (*a <= 100) { /* -- if block -- */ }
    mainBlock.If("*a", 100, BooleanOp::LessEqual, &ifBlock);
    
    // for (int i = 0; i < 30; ++i) { /* -- for block -- */ }
    mainBlock.For(30, &forBlock);
    
    mainBlock.SetJumpPoint(3); // this location is jump point 3
    mainBlock.Jump(3); // jump to jump point 3
    
    mainBlock.Break(); // break from loop
공통적으로 마지막 인자로 ASMBlock의 포인터를 넘겨받습니다.

ASMBlock::For(uint16_t, ASMBlock *)은 두번째 인자로 주어지는 ASMBlock을 uint16_t회 반복하며 주석의 int i에 해당하는 변수에는 접근할 수 없습니다.

while (2 < 3) 과 같은 바보짓을 방지하기 위하여 While과 If의 첫번째 인자에는 uint16_t를 넣을 수 없습니다.

다음은 간단한 While 문 작성 예시입니다.

    /*
    int i = 0;
    while (i < 100)
    {
	    if (i == 77)
		    break;
		i++;
	}
	*/
	ASMBlock mainBlock, whileBlock, ifBlock;
	mainBlock.Assign("i", 0);
	mainBlock.While("i", 100, BooleanOp::LessStrict, &whileBlock);
	whileBlock.If("i", 77, BooleanOp::Equal, &ifBlock);
	ifBlock.Break();
	whileBlock.AddAssign("i", "i", 1);
순서대로 작성해도 되고 아무렇게나 작성해도 됩니다. 다만 같은 ASMBlock 내의 Statements 들은 순서대로 위치해야 합니다.

    ASMBlock mainBlock, whileBlock, ifBlock;
    ifBlock.Break();
    whileBlock.If("i", 77, BooleanOp::Equal, &ifBlock);
    mainBlock.Assign("i", 0);
    mainBlock.While("i", 100, BooleanOp::LessStrict, &whileBlock);
    whileBlock.AddAssign("i", "i", 1);
순서가 엉망이지만 mainBlock.~ 끼리의 상대적 순서, whileBlock.~ 끼리의 상대적 순서는 유지되었습니다.

모든 변수가 전역변수이므로 변수이름이 금방 바닥날 수 있습니다. 이름이 필요하지 않는 1회성 변수의 생성은 다음 함수를 사용하세요.

	std::string temp = AddressManager::GetInstance()->GetTemp();
temp를 이름 없는 변수로 사용할 수 있습니다.

    mainBlock.Assign(temp, 500); // temp = 500
    mainBlock.AddAssign("a", temp, 200); // a = temp + 200
    // better than
    // mainBlock.Assign("variableNameYouShouldComeUpWithJustToUseOnce", 500);
    // mainBlock.AddAssign("a", "variableNameYouShouldComeUpWithJustToUseOnce", 200);
std::string temp = GetTemp()를 다시 호출하면 새 변수를 받습니다. 기존의 temp는 따로 저장해두지 않으면 다시 접근할 방법이 없어집니다. 1회성 변수에만 사용하세요.

GetTemp()의 return value는 "__tempKorimart" + 숫자이므로 이것을 변수이름으로 사용하지 마세요.

앞서 설명한 몇몇 Statement는 이름 없는 변수를 사용하고 inline으로 결과물에 들어가므로 코드에 많이 등장하면 많은 일회성 변수를 만들어 낼 수 있으며 RAM의 낭비가 될 수 있습니다. 하지만 경험상 ROM이 아닌 RAM의 용량은 넉넉하므로 신경쓰지 않으셔도 됩니다.

## Convenience Functions
편리한 그래픽 함수들입니다. nand2tetris CPU emulator 는 512x256의 스크린을 제공합니다. 성능상의 이유로 다음 함수들은 이를 16x16의 정사각형으로 나눈 32x16 좌표계를 사용합니다(픽셀단위가 아닌 정사각형 단위의 값을 넣어야함; width = 1은 16픽셀을 의미). 좌측 상단의 좌표는 (0, 0) 이며 낮아질수록 y의 값이 증가합니다.

주의 : 모든 함수는 inline 이므로 다음 함수들을 많이 쓸 수록 결과물의 길이가 길어져 ROM을 많이 잡아먹음

    // 32x16 좌표계의 
    struct AREA
    {
	    std::string x; // 사각형의 좌단
	    std::string y; // 사각형의 상단
	    std::string width;
	    std::string height;
    };
    void ASMBlock::InvalidateRect(AREA& area, bool bIsWhite = true);
AREA 구조체에 채워진 변수의 값으로 화면을 지웁니다. bIsWhite이 참이면 흰색으로, 거짓이면 검은색으로 지웁니다.

    void ASMBlock::DrawLine(AREA& area, bool bHorizontal = true);
AREA 구조체에 채워진 변수의 값으로 화면에 직선을 그립니다. bHorizontal =\= true 이면 사각형의 최상단에 가로 직선을, bHorizontal == false이면 사각형의 최좌단에 세로 직선을 그립니다.

    void ASMBlock::DrawGrid(AREA& area);
AREA 구조체에 채워진 변수의 값으로 화면에 격자를 그립니다. 격자는 가로 16px 세로 16px 크기로 생성됩니다.

    struct RECT
	{
		uint16_t x;
		uint16_t y;
		uint16_t width;
		uint16_t height;
	};
    void ASMBlock::DrawImage(const std::string& fileName, RECT rt);
fileName 위치의 .txt를 찾아 RECT 구조체에 채워진 상수의 값에 해당하는 화면의 위치에 이미지를 그립니다. 이미지의 크기는 16의 배수이어야 합니다(그래야 width와 height에 정수가 들어감). 위치는 컴파일타임에 제공되므로 고정되며 함수는 inline으로 결과물에 들어가므로 이미지의 화면상 위치를 변경하고 싶을 때에는 부득이하게 결과물의 길이가 두배가 되는 비용을 치뤄야 합니다. 이는 stack 및 subroutine function call 구현을 회피하기 위한 조치입니다.

이미지를 같은 위치에 다른 상황에 다시 그리고 싶을 때에는 함수는 한번만 제공하고 각기 다른 상황에서 ASMBlock::Jump를 이용하여 흡사 subroutine과 같은 구현을 하는것을 추천합니다. ROM의 용량이 한정적이기 때문에 ASMBlock::DrawImage()를 적당한 크기의 이미지로 서너번만 호출해도 ROM이 꽉차게됩니다.

.txt파일의 생성에는 다음 사이트를 이용하세요.
[https://www.dcode.fr/binary-image](https://www.dcode.fr/binary-image)
