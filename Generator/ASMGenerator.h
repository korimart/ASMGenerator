#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <cmath>

#define ADDRMAX 0x6000
#define SCREEN 0x4000
#define KEYBOARD 0x6000
#define ARROWUP 131
#define ARROWDOWN 133
#define ARROWRIGHT 132
#define ARROWLEFT 130

enum class BooleanOp
{
    LessStrict,
    LessEqual,
    Equal,
    NotEqual,
    GreaterStrict,
    GreaterEqual
};

enum class StatementType
{
    Assign,
	AssignV,
    AddAssignVC,
    AddAssignVV,
    MultiplyAssignVC,
    MultiplyAssignVV,
	SubtractAssignVC,
	SubtractAssignVV,
	BitwiseAndAssignVC,
	BitwiseAndAssignVV,
	BitwiseOrAssignVC,
	BitwiseOrAssignVV,
    WhileVC,
    WhileVV,
    IfVC,
    IfVV,
	For,
	Break,
	SetJumpPoint,
	Jump,
	InvalidateRect,
	DrawLine,
	DrawGrid,
	DrawImage
};

struct RECT
{
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
};

struct AREA
{
	std::string x;
	std::string y;
	std::string width;
	std::string height;
};

class ASMBlock;

struct Statement
{
    StatementType type;
    uint16_t value;
    union U
    {
		U() : str() {}
		~U() {}
        uint16_t constant;
        std::string str;
    } op1;

    union U2
    {
		U2() : str() {}
		~U2() {}
        uint16_t constant;
        std::string str; 
    } op2;

    BooleanOp condOp;
    ASMBlock *block;
	std::string targetName;
	uint16_t addr;
	AREA area;
	RECT rt;
};

class ASMBlock
{
public:
	void Init();

    void Assign(const std::string &varName, uint16_t value);
	void Assign(const std::string &varName, const std::string &op);
    void AddAssign(const std::string &varName, const std::string &op1, uint16_t op2);
    void AddAssign(const std::string &varName, const std::string &op1, const std::string &op2);
    void MultiplyAssign(const std::string &varName, const std::string &op1, uint16_t op2);
    void MultiplyAssign(const std::string &varName, const std::string &op1, const std::string &op2);
	void SubtractAssign(const std::string &varName, const std::string &op1, uint16_t op2);
	void SubtractAssign(const std::string &varName, const std::string &op1, const std::string &op2);
	void BitwiseAndAssign(const std::string &varName, const std::string &op1, uint16_t op2);
	void BitwiseAndAssign(const std::string &varName, const std::string &op1, const std::string &op2);
	void BitwiseOrAssign(const std::string &varName, const std::string &op1, uint16_t op2);
	void BitwiseOrAssign(const std::string &varName, const std::string &op1, const std::string &op2);
    void While(const std::string &op1, uint16_t op2, BooleanOp operation, ASMBlock *block);
    void While(const std::string &op1, const std::string &op2, BooleanOp operation, ASMBlock *block);
    void If(const std::string &op1, uint16_t op2, BooleanOp operation, ASMBlock *Block);
    void If(const std::string &op1, const std::string &op2, BooleanOp operation, ASMBlock *Block);
	void For(uint16_t numCycles, ASMBlock* Block);
	void Break();
	void SetJumpPoint(unsigned point);
	void Jump(unsigned point);

	void InvalidateRect(AREA & area, bool bIsWhite = true);
	void DrawLine(AREA& area, bool bVertical = true);
	void DrawGrid(AREA& area);
	void DrawImage(const std::string& fileName, RECT rt);

    void GetASM(std::stringstream &out);
    
public:
	static std::string NEGONE;

private:
	void SetBreakPoint(uint16_t breakpoint);
	void Jump(std::stringstream& out, BooleanOp op);
	inline void GetPointedVal2AReg(std::stringstream &out, const std::string &varName);
	inline void GetVal2AReg(std::stringstream &out, const std::string &varName);
	inline void LoadAReg(std::stringstream &out, const std::string &varName);
	static void DrawImage(std::stringstream& out, const Statement *pStatement);

    std::vector<std::unique_ptr<Statement>> mStatements;
	uint16_t mBreakPoint = 0;
};

class AddressManager
{
public:
    static AddressManager *GetInstance();

    // return invalid address if failed
    uint16_t GetAddress(const std::string &varName);
	std::string GetTemp();
	int GetNextUniqueID(void);

private:
    AddressManager() = default;
    ~AddressManager() = delete;
    static AddressManager *Instance;
    std::unordered_map<std::string, uint16_t> mVariables;
    uint16_t mNextAddress = 0;
	int mNextUniqueID = 0;
};

