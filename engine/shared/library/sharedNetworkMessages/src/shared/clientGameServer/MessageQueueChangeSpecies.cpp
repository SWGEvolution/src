//========================================================================
//
// MessageQueueChangeSpecies.cpp
//
// copyright 2005 Sony Online Entertainment, Inc.
// All rights reserved.
//
//========================================================================

#include "sharedNetworkMessages/FirstSharedNetworkMessages.h"
#include "sharedNetworkMessages/MessageQueueChangeSpecies.h"

#include "sharedFoundation/MemoryBlockManager.h"
#include "sharedFoundation/ExitChain.h"
#include "sharedFoundation/GameControllerMessage.h"
#include "sharedNetworkMessages/ControllerMessageFactory.h"

//===================================================================

CONTROLLER_MESSAGE_ALLOW_FROM_CLIENT_IMPLEMENTATION(MessageQueueChangeSpecies, CM_setSpeciesTemplate);

//----------------------------------------------------------------------

MessageQueueChangeSpecies::MessageQueueChangeSpecies(std::string const & speciesTemplate) :
m_speciesTemplate(speciesTemplate)
{
}

//----------------------------------------------------------------------

MessageQueueChangeSpecies::~MessageQueueChangeSpecies()
{
}

//----------------------------------------------------------------------

void MessageQueueChangeSpecies::pack(const MessageQueue::Data* const data, Archive::ByteStream & target)
{
	MessageQueueChangeSpecies const * const msg = safe_cast<const MessageQueueChangeSpecies*>(data);
	if (msg)
	{
		Archive::put(target, msg->getSpeciesTemplate());
	}
}

//-----------------------------------------------------------------------

MessageQueue::Data * MessageQueueChangeSpecies::unpack(Archive::ReadIterator & source)
{
	std::string speciesTemplate;

	Archive::get(source, speciesTemplate);
	
	return new MessageQueueChangeSpecies(speciesTemplate);
}

//----------------------------------------------------------------------

