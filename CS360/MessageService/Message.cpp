#include "Message.h"

	Message::Message()
	{

	}
 	Message::~Message()
	{
		
	}
 	string Message::getOriginal()
	{
		return original;
	}
 	string Message::getCommand()
	{
		return command;
	}
 	string* Message::getParams()
	{
		return params;
	}
 	string Message::getValue()
	{
		return value;
	}
 	bool Message::getNeeded()
	{
		return needed;
	}

 	void Message::setOriginal(string original)
	{
		this->original = original;
	}
 	void Message::setCommand(string command)
	{
		this->command = command;
	}
 	void Message::setParams(string file, string bytes)
	{
		this->params[0] = file;
		this->params[1] = bytes;
	}
 	void Message::setValue(string value)
	{
		this->value = value;
	}
 	void Message::setNeeded(bool needed)
	{
		this->needed = needed;
	}
	string Message::toString()
	{
		return "Stored a file called" + params[0] + " with " + params[1] + " bytes\n";
	}
	string Message::seeMessage(int num)
	{
		string numS;
		if(num == 1){numS = "1";}
		if(num == 2){numS = "2";}
		if(num == 3){numS = "3";}
		string mess;
		mess += "--------------------seeMessage" + numS + "--------------------\n";
		mess += "Command:: " + command + "\n";
		mess += "Param[0]:: " + params[0] +"\n";
		mess += "Param[1]:: " + params[1] +"\n";
		mess += "Value:: " + value +"\n";
		mess +=  "Needed:: " + needed + '\n';
		mess += "--------------------------------------------------";
		return mess;
	}
	
	string Message::getName()
	{
		return name;
	}
	
	void Message::setName(string nameIn)
	{
		name = nameIn;
	}


