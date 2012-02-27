#include "stdafx.h"
#include "InputMultiplexer.h"

/** An {@link InputProcessor} that delegates to an ordered list of other InputProcessors. Delegation for an event stops if a
* processor returns true, which indicates that the event was handled.*/

InputMultiplexer::InputMultiplexer()
{
}

InputMultiplexer::InputMultiplexer(InputProcessor* processors[], int numProcessors)
{
	for (int i = 0; i < numProcessors; i++)
		m_processors.push_back(processors[i]);
}

void InputMultiplexer::addProcessor(int index, InputProcessor* processor)
{
	InputProcessorsListIterator it = m_processors.begin();
	while(index--)
		it++;
	m_processors.insert(it, processor);
}

void InputMultiplexer::removeProcessor(int index)
{
	InputProcessorsListIterator it = m_processors.begin();
	while(index--)
		it++;
	m_processors.remove(*it);
}

void InputMultiplexer::addProcessor(InputProcessor* processor)
{
	m_processors.push_back(processor);
}

void InputMultiplexer::removeProcessor(InputProcessor* processor)
{
	m_processors.remove(processor);
}

/**
* @return the number of m_processors in this multiplexer
*/
int InputMultiplexer::size()
{
	return m_processors.size();
}

void InputMultiplexer::clear()
{
	m_processors.clear();
}

void InputMultiplexer::setProcessors(InputProcessorsList processors)
{
	m_processors = processors;
}

InputMultiplexer::InputProcessorsList InputMultiplexer::getProcessors()
{
	return m_processors;
}

bool InputMultiplexer::keyDown(int keycode)
{
	for(InputProcessorsListIterator it; it != m_processors.end(); it++)
		if((*it)->keyDown(keycode)) 
			return true;
	return false;
}

bool InputMultiplexer::keyUp(int keycode)
{
	for(InputProcessorsListIterator it; it != m_processors.end(); it++)
		if((*it)->keyUp(keycode)) 
			return true;
	return false;
}

bool InputMultiplexer::keyTyped(char character)
{
	for(InputProcessorsListIterator it; it != m_processors.end(); it++)
		if((*it)->keyTyped(character)) 
			return true;
	return false;
}

bool InputMultiplexer::touchDown(int x, int y, int pointer, int button)
{
	for(InputProcessorsListIterator it; it != m_processors.end(); it++)
		if((*it)->touchDown(x, y , pointer, button)) 
			return true;
	return false;
}

bool InputMultiplexer::touchUp(int x, int y, int pointer, int button)
{
	for(InputProcessorsListIterator it; it != m_processors.end(); it++)
		if((*it)->touchUp(x, y , pointer, button)) 
			return true;
	return false;
}

bool InputMultiplexer::touchDragged(int x, int y, int pointer)
{
	for(InputProcessorsListIterator it; it != m_processors.end(); it++)
		if((*it)->touchDragged(x, y , pointer)) 
			return true;
}

bool InputMultiplexer::touchMoved(int x, int y)
{
	for(InputProcessorsListIterator it; it != m_processors.end(); it++)
		if((*it)->touchMoved(x, y)) 
			return true;
}

bool InputMultiplexer::scrolled(int amount)
{
	for(InputProcessorsListIterator it; it != m_processors.end(); it++)
		if((*it)->scrolled(amount)) 
			return true;
}
