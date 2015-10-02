#include <string>
using namespace std;

 class Message 
{
 private:
 	string original;
 	string name; 
	string command;
	string params[2];
	string value;
	bool needed;

 public:
	Message();
	~Message();
	string getOriginal();
	string getCommand();
	string* getParams();
	string getValue();
	string getName();
	bool getNeeded();

	void setName(string nameIn);
	void setOriginal(string original);
	void setCommand(string command);
	void setParams(string file, string bytes);
	void setValue(string value);
	void setNeeded(bool needed);
	string toString();
	string seeMessage(int);
 };