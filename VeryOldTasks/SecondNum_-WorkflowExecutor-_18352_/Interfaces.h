#include <iostream>
#include<string>
#include <vector>
#include <map>
#include <fstream>
#include<algorithm>
#include<exception>
#include<stdexcept>
#include<ctime>
//MemoryLeaks
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
//---------------------------
class Parser {
	std::ifstream workFile;
	size_t* numbers;
	size_t sizeOfNumbers;
public:
	Parser(const std::string Name);
	bool endOfInstruction();
	std::string getNextComand();
	size_t getComandNum(std::string& str);
	std::string getComandName(std::string& str);
	std::vector<std::string> getArgs(std::string& str);
	~Parser();
	const size_t getNum(size_t ind) const;
	const size_t getsize() const;
};
class IWorker;
class Validator {
	//	std::map<size_t, std::pair<IWorker*, std::vector<std::string>>> & m;
	//	std::map<std::string, IWorker *> &i;
	const Parser& p;
	std::map<size_t, std::string> & check;
public:
	Validator(std::map<size_t, std::string> & other, const Parser& otherP);
	void correctBlocks();
};


class IWorker {
protected:
	static std::string * resorce;
	void initData();
public:
	virtual void toDo(std::vector<std::string> V) = 0;
};
//std::string IWorker::resorce = nullptr;

class Read : public IWorker {
public:
	Read();
	void toDo(std::vector<std::string> V);
	~Read();
};
class Write : public IWorker {
public:
	Write() {}
	void toDo(std::vector<std::string> V);

};
class Grep :public IWorker {
public:
	//	Grep() {}
	void toDo(std::vector<std::string> V);

};
class Sort :public IWorker {
public:
	//	Sort() {}
	void toDo(std::vector<std::string> V);
};
class Dump :public IWorker {
public:
	//	Dump() {}
	void toDo(std::vector<std::string> V);
};
class Replace :public IWorker {
public:
	//	Replace() {}
	void toDo(std::vector<std::string> V);
};
class MyError : std::exception {
	const char* what() const;
};

