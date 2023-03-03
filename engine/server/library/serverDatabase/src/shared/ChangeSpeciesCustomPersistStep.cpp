// ======================================================================
//
// ChangeSpeciesCustomPersistStep.cpp
// copyright (c) 2001 Sony Online Entertainment
//
// ======================================================================

#include "serverDatabase/FirstServerDatabase.h"
#include "serverDatabase/ChangeSpeciesCustomPersistStep.h"

#include "serverDatabase/CharacterQueries.h"
#include "serverDatabase/DataLookup.h"
#include "serverDatabase/DatabaseProcess.h"
#include "serverNetworkMessages/MessageToMessage.h"
#include "serverNetworkMessages/ChangeSpeciesMessage.h"
#include "serverNetworkMessages/TransferCharacterData.h"
#include "serverNetworkMessages/TransferCharacterDataArchive.h"
#include "sharedDatabaseInterface/DbSession.h"
#include "sharedFoundation/FormattedString.h"
#include "sharedLog/Log.h"
#include "sharedNetworkMessages/GenericValueTypeMessage.h"

// ======================================================================

namespace ChangeSpeciesCustomPersistStepNamespace
{
	std::map<NetworkId, int> s_pendingChangeSpeciesCustomPersistStep;
}

using namespace ChangeSpeciesCustomPersistStepNamespace;

// ======================================================================

ChangeSpeciesCustomPersistStep::ChangeSpeciesCustomPersistStep(int8 changeSpeciesMessageSource, uint32 stationId, const NetworkId &characterId, const Unicode::String &newSpeciesTemplate, const NetworkId &requestedBy, const TransferCharacterData * requestData) :
		m_changeSpeciesMessageSource(changeSpeciesMessageSource),
		m_stationId(stationId),
		m_characterId(characterId),
		m_newSpeciesTemplate(new Unicode::String(newSpeciesTemplate)),
		m_requestedBy(requestedBy),
		m_success(false),
		m_requestData(0)
{	
	if(requestData)
	{
		m_requestData = new TransferCharacterData(*requestData);
	}

	if (m_characterId.isValid())
	{
		std::map<NetworkId, int>::iterator iterFind = s_pendingChangeSpeciesCustomPersistStep.find(m_characterId);
		if (iterFind != s_pendingChangeSpeciesCustomPersistStep.end())
			++(iterFind->second);
		else
			s_pendingChangeSpeciesCustomPersistStep.insert(std::make_pair(m_characterId, 1));
	}
}

// ----------------------------------------------------------------------

ChangeSpeciesCustomPersistStep::~ChangeSpeciesCustomPersistStep()
{
	delete m_newSpeciesTemplate;
	delete m_requestData;
	m_newSpeciesTemplate  = 0;
	m_requestData = 0;

	if (m_characterId.isValid())
	{
		std::map<NetworkId, int>::iterator iterFind = s_pendingChangeSpeciesCustomPersistStep.find(m_characterId);
		if (iterFind != s_pendingChangeSpeciesCustomPersistStep.end())
		{
			if (iterFind->second <= 1)
				s_pendingChangeSpeciesCustomPersistStep.erase(iterFind);
			else
				--(iterFind->second);
		}

		// let CentralServer know that the request has
		// been completed, so CentralServer will allow the character to log back in
		if (static_cast<ChangeSpeciesMessageEx::ChangeSpeciesMessageSource>(m_changeSpeciesMessageSource) == ChangeSpeciesMessageEx::CSMS_player_request)
		{
			GenericValueTypeMessage<std::pair<unsigned int, NetworkId> > const msg("ChangeSpeciesRequestCompleted", std::make_pair(static_cast<unsigned int>(m_stationId), m_characterId));
			DatabaseProcess::getInstance().sendToCentralServer(msg, true);
		}
	}
}

// ----------------------------------------------------------------------

bool ChangeSpeciesCustomPersistStep::beforePersist(DB::Session *session)
{
	UNREF(session);
	return true;
}

// ----------------------------------------------------------------------

bool ChangeSpeciesCustomPersistStep::afterPersist(DB::Session *session)
{
	m_success=true;
	return true;
}

// ----------------------------------------------------------------------

void ChangeSpeciesCustomPersistStep::onComplete()
{
	if (! m_requestData)
	{
		if (m_success)
		{
			// send to login server (by way of central)
			ChangeSpeciesMessageEx msg(static_cast<ChangeSpeciesMessageEx::ChangeSpeciesMessageSource>(m_changeSpeciesMessageSource), m_stationId, m_characterId, *m_newSpeciesTemplate, m_requestedBy);
			DatabaseProcess::getInstance().sendToCentralServer(msg,true);

			// have all the game servers update
			DatabaseProcess::getInstance().sendToAllGameServers(msg,true);

		}
	}
	else
	{
		TransferCharacterData replyData(*m_requestData);
		//replyData.setIsValidName(m_success);
		
		GenericValueTypeMessage<TransferCharacterData> reply("TransferChangeSpeciesReplyFromDatabase", replyData);
		DatabaseProcess::getInstance().sendToCentralServer(reply, true);
	}

}

// ----------------------------------------------------------------------

bool ChangeSpeciesCustomPersistStep::hasPendingChangeSpeciesCustomPersistStep(const NetworkId &characterId)
{
	return (s_pendingChangeSpeciesCustomPersistStep.count(characterId) > 0);
}

// ======================================================================
