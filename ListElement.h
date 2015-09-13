#ifndef __LIST_ELEMENT_H__
#define __LIST_ELEMENT_H__

#include <string>

using std::string;

struct ConclusionQueueElement
{
	public:
		ConclusionQueueElement()
			: variableName(""), variableListIndex(-1), clauseVariableListIndex(-1)
		{}
		ConclusionQueueElement(string name, int variableIndex, int clauseIndex)
			: variableName(name), variableListIndex(variableIndex), clauseVariableListIndex(clauseIndex)
		{}
		ConclusionQueueElement(string name, int clauseIndex)
			: variableName(name), variableListIndex(-1), clauseVariableListIndex(clauseIndex)
		{}
		string variableName;
		int variableListIndex;
		int clauseVariableListIndex;
};

class VariableElement
{
	public:
		VariableElement() : variableName(""), variableValue(-1)
		{}
		VariableElement(string name, int val) : variableName(name), variableValue(val)
		{}
		string variableName;
		int variableValue;

	private:
};

class ClauseVariableElement
{
	public:
		ClauseVariableElement() : clauseName(""), clauseValue(-1)
		{}
		ClauseVariableElement(string name, int val) : clauseName(name), clauseValue(val)
		{}
		string clauseName;
		int clauseValue;
};

#endif