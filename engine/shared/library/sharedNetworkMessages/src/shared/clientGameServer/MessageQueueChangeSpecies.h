//========================================================================
//
// MessageQueueChangeSpecies.h
//
// copyright 2005 Sony Online Entertainment, Inc.
// All rights reserved.
//
//========================================================================


#ifndef INCLUDED_MessageQueueChangeSpecies_H
#define INCLUDED_MessageQueueChangeSpecies_H

#include "sharedFoundation/MessageQueue.h"
#include "sharedNetworkMessages/ControllerMessageMacros.h"

class MemoryBlockManager;

class MessageQueueChangeSpecies : public MessageQueue::Data
{
	CONTROLLER_MESSAGE_INTERFACE;

public:

	         MessageQueueChangeSpecies(std::string const & speciesTemplate);
	virtual ~MessageQueueChangeSpecies();

	std::string const & getSpeciesTemplate() const;

private:

	std::string m_speciesTemplate;

private:
	MessageQueueChangeSpecies();
	MessageQueueChangeSpecies(const MessageQueueChangeSpecies &);
	MessageQueueChangeSpecies & operator=(const MessageQueueChangeSpecies &);
};

//----------------------------------------------------------------------

inline std::string const & MessageQueueChangeSpecies::getSpeciesTemplate() const
{
	return m_speciesTemplate;
}

//----------------------------------------------------------------------

#endif	// INCLUDED_MessageQueueChangeSpecies_H
