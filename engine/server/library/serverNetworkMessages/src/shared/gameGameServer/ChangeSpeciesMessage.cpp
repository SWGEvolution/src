//========================================================================
//
// ChangeSpeciesMessage.cpp
//
// copyright 2002 Sony Online Entertainment
//
//========================================================================

#include "serverNetworkMessages/FirstServerNetworkMessages.h"
#include "serverNetworkMessages/ChangeSpeciesMessage.h"

#include "UnicodeUtils.h"

//-----------------------------------------------------------------------

ChangeSpeciesMessage::ChangeSpeciesMessage(const NetworkId &characterId, const Unicode::String &newSpeciesTemplate, const NetworkId &requestedBy) :
	GameNetworkMessage("ChangeSpeciesMessage"),
	m_characterId(characterId),
	m_newSpeciesTemplate(newSpeciesTemplate),
	m_requestedBy(requestedBy)
{
	addVariable(m_characterId);
	addVariable(m_newSpeciesTemplate);
	addVariable(m_requestedBy);
}

//-----------------------------------------------------------------------

ChangeSpeciesMessage::ChangeSpeciesMessage(Archive::ReadIterator & source) :
		GameNetworkMessage("ChangeSpeciesMessage"),
		m_characterId(),
		m_newSpeciesTemplate(),
		m_requestedBy()
{
	addVariable(m_characterId);
	addVariable(m_newSpeciesTemplate);
	addVariable(m_requestedBy);
	unpack(source);
}

//-----------------------------------------------------------------------

ChangeSpeciesMessage::~ChangeSpeciesMessage()
{
}

//========================================================================

ChangeSpeciesMessageEx::ChangeSpeciesMessageEx(ChangeSpeciesMessageSource ChangeSpeciesMessageSource, uint32 stationId, const NetworkId &characterId, const Unicode::String &newSpeciesTemplate, const NetworkId &requestedBy) :
	GameNetworkMessage("ChangeSpeciesMessageEx"),
	m_stationId(stationId),
	m_characterId(characterId),
	m_newSpeciesTemplate(newSpeciesTemplate),
	m_requestedBy(requestedBy),
	m_ChangeSpeciesMessageSource(static_cast<int8>(ChangeSpeciesMessageSource))
{

	addVariable(m_stationId);
	addVariable(m_characterId);
	addVariable(m_newSpeciesTemplate);
	addVariable(m_requestedBy);
	addVariable(m_ChangeSpeciesMessageSource);
}

//-----------------------------------------------------------------------

ChangeSpeciesMessageEx::ChangeSpeciesMessageEx(Archive::ReadIterator & source) :
		GameNetworkMessage("ChangeSpeciesMessageEx"),
		m_stationId(),
		m_characterId(),
		m_newSpeciesTemplate(),
		m_requestedBy(),
		m_ChangeSpeciesMessageSource()
{
	addVariable(m_stationId);
	addVariable(m_characterId);
	addVariable(m_newSpeciesTemplate);
	addVariable(m_requestedBy);
	addVariable(m_ChangeSpeciesMessageSource);
	unpack(source);
}

//-----------------------------------------------------------------------

ChangeSpeciesMessageEx::~ChangeSpeciesMessageEx()
{
}

//-----------------------------------------------------------------------
