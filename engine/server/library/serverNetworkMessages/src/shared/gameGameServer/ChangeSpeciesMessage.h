//========================================================================
//
// ChangeSpeciesMessage.h
//
// copyright 2001 Sony Online Entertainment
//
//========================================================================

#ifndef	_INCLUDED_ChangeSpeciesMessage_H
#define	_INCLUDED_ChangeSpeciesMessage_H

//-----------------------------------------------------------------------

#include "sharedNetworkMessages/GameNetworkMessage.h"
#include "unicodeArchive/UnicodeArchive.h"

//-----------------------------------------------------------------------

/**
 * Sent from:  Game Server
 * Sent to:    DBProcess
 * Action:     Change player species.
 *             
 *
 * Sent from:  DBProcess
 * Send to:    LoginServer (via Central)
 * Action:     Update the character's species in the login database.
 */
class ChangeSpeciesMessage : public GameNetworkMessage
{
  public:
	ChangeSpeciesMessage  (const NetworkId &characterId, const Unicode::String &newSpeciesTemplate, const NetworkId &requestedBy);
	ChangeSpeciesMessage  (Archive::ReadIterator & source);
	~ChangeSpeciesMessage ();

  public:
	const NetworkId &       getCharacterId       () const;
	const Unicode::String & getNewSpeciesTemplate     () const;
	const NetworkId &       getRequestedBy       () const;
	
  private:
	Archive::AutoVariable<NetworkId>        m_characterId;
	Archive::AutoVariable<Unicode::String>  m_newSpeciesTemplate;
	Archive::AutoVariable<NetworkId>        m_requestedBy;

  private:
	ChangeSpeciesMessage            (const ChangeSpeciesMessage&);
	ChangeSpeciesMessage& operator= (const ChangeSpeciesMessage&);
};

// ======================================================================

inline const NetworkId &ChangeSpeciesMessage::getCharacterId() const
{
	return m_characterId.get();
}

// ----------------------------------------------------------------------

inline const Unicode::String &ChangeSpeciesMessage::getNewSpeciesTemplate() const
{
	return m_newSpeciesTemplate.get();
}

// ----------------------------------------------------------------------

inline const NetworkId &ChangeSpeciesMessage::getRequestedBy() const
{
	return m_requestedBy.get();
}

// ======================================================================

class ChangeSpeciesMessageEx : public GameNetworkMessage
{
public:
	enum ChangeSpeciesMessageSource {CSMS_player_request};

  public:
	ChangeSpeciesMessageEx  (ChangeSpeciesMessageSource ChangeSpeciesMessageSource, uint32 stationId, const NetworkId &characterId, const Unicode::String &newSpeciesTemplate, const NetworkId &requestedBy);
	ChangeSpeciesMessageEx  (Archive::ReadIterator & source);
	~ChangeSpeciesMessageEx ();

  public:
	uint32                  getStationId         () const;
	const NetworkId &       getCharacterId       () const;
	const Unicode::String & getNewSpeciesTemplate     () const;
	const NetworkId &       getRequestedBy       () const;
	ChangeSpeciesMessageSource getChangeSpeciesMessageSource () const;

  private:
	Archive::AutoVariable<uint32>           m_stationId;
	Archive::AutoVariable<NetworkId>        m_characterId;
	Archive::AutoVariable<Unicode::String>  m_newSpeciesTemplate;
	Archive::AutoVariable<NetworkId>        m_requestedBy;
	Archive::AutoVariable<int8>             m_ChangeSpeciesMessageSource;

  private:
	ChangeSpeciesMessageEx            (const ChangeSpeciesMessageEx&);
	ChangeSpeciesMessageEx& operator= (const ChangeSpeciesMessageEx&);
};

// ======================================================================

inline uint32 ChangeSpeciesMessageEx::getStationId() const
{
	return m_stationId.get();
}

// ----------------------------------------------------------------------

inline const NetworkId &ChangeSpeciesMessageEx::getCharacterId() const
{
	return m_characterId.get();
}

// ----------------------------------------------------------------------

inline const Unicode::String &ChangeSpeciesMessageEx::getNewSpeciesTemplate() const
{
	return m_newSpeciesTemplate.get();
}

// ----------------------------------------------------------------------


inline const NetworkId &ChangeSpeciesMessageEx::getRequestedBy() const
{
	return m_requestedBy.get();
}

// ----------------------------------------------------------------------

inline ChangeSpeciesMessageEx::ChangeSpeciesMessageSource ChangeSpeciesMessageEx::getChangeSpeciesMessageSource () const
{
	return static_cast<ChangeSpeciesMessageSource>(m_ChangeSpeciesMessageSource.get());
}

// ----------------------------------------------------------------------

#endif
