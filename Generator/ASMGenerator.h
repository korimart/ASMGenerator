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
	AssignAtAddr,
	AssignAtAddrV,
    AddAssignVC,
    AddAssignVV,
    MultiplyAssignVC,
    MultiplyAssignVV,
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

class ASMImage
{
public:
	ASMImage(unsigned width, unsigned Height);
	void Dot(unsigned x, unsigned y, bool bBlack = true);
	void LoadImageFromFile(const std::string& fileName, unsigned width, unsigned height);
	unsigned Width() const;
	unsigned Height() const;
	std::vector<uint16_t> Data() const;

private:
	unsigned mWidth;
	unsigned mHeight;
	std::vector<uint16_t> mImageData;
};

class ASMBlock
{
public:
    void Assign(const std::string &varName, uint16_t value);
	void AssignAtAddress(uint16_t addr, uint16_t value);
	void AssignAtAddress(const std::string& varName, uint16_t value);
    void AddAssign(const std::string &varName, const std::string &op1, uint16_t op2);
    void AddAssign(const std::string &varName, const std::string &op1, const std::string &op2);
    void MultiplyAssign(const std::string &varName, const std::string &op1, uint16_t op2);
    void MultiplyAssign(const std::string &varName, const std::string &op1, const std::string &op2);
	void SubtractAssign();
	void BitwiseAndAssign();
	void BitwiseOrAssign();
    void While(const std::string &op1, uint16_t op2, BooleanOp operation, ASMBlock *block);
    void While(const std::string &op1, const std::string &op2, BooleanOp operation, ASMBlock *block);
    void If(const std::string &op1, uint16_t op2, BooleanOp operation, ASMBlock *Block);
    void If(const std::string &op1, const std::string &op2, BooleanOp operation, ASMBlock *Block);
	void For(uint16_t numCycles, ASMBlock* Block);
	void Break();

	uint16_t LoadASMImage(const ASMImage& image);
	void ClearRegion(RECT region);
	void DrawSubimage(uint16_t imageID, RECT subimage, unsigned screenX, unsigned screenY);

    void GetASM(std::stringstream &out);
    
private:
	void SetBreakPoint(uint16_t breakpoint);
	void Jump(std::stringstream& out, BooleanOp op);

    std::vector<std::unique_ptr<Statement>> mStatements;
	// ID : vector of (address, value) pairs
	std::unordered_map<uint16_t, std::unique_ptr<ASMImage>> mImages;
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

