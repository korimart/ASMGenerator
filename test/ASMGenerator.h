#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

#define ADDRMAX 0x6000

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
	ClearRegion
};

struct RECT
{
	unsigned left;
	unsigned right;
	unsigned top;
	unsigned bottom;
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
	RECT rt;
};

class ASMBlock
{
public:
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

    void GetASM(std::stringstream &out);
    
private:
	void SetBreakPoint(uint16_t breakpoint);
	void Jump(std::stringstream& out, BooleanOp op);
	inline void GetPointedVal2AReg(std::stringstream &out, const std::string &varName);
	inline void GetVal2AReg(std::stringstream &out, const std::string &varName);
	inline void LoadAReg(std::stringstream &out, const std::string &varName);

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

