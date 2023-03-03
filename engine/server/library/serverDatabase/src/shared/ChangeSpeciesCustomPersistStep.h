// ======================================================================
//
// ChangeSpeciesCustomPersistStep.h
// copyright (c) 2001 Sony Online Entertainment
//
// ======================================================================

#ifndef INCLUDED_ChangeSpeciesCustomPersistStep_H
#define INCLUDED_ChangeSpeciesCustomPersistStep_H

// ======================================================================

#include "serverDatabase/CustomPersistStep.h"
#include "sharedFoundation/NetworkId.h"

class NetworkId;
class TransferCharacterData;

// ======================================================================

class ChangeSpeciesCustomPersistStep : public CustomPersistStep
{
  public:
	ChangeSpeciesCustomPersistStep(int8 changeSpeciesMessageSource, uint32 stationId, const NetworkId &characterId, const Unicode::String &newSpeciesTemplate, const NetworkId &requestedBy, const TransferCharacterData * requestData);
	~ChangeSpeciesCustomPersistStep();
	
	virtual bool beforePersist (DB::Session *session);
	virtual bool afterPersist  (DB::Session *session);
	virtual void onComplete    ();

	static bool hasPendingChangeSpeciesCustomPersistStep(const NetworkId &characterId);

  private:
	int8              m_changeSpeciesMessageSource;
	uint32            m_stationId;
	NetworkId         m_characterId;
	Unicode::String * m_newSpeciesTemplate;
	NetworkId         m_requestedBy;
	bool              m_success;
	TransferCharacterData *  m_requestData;
};

// ======================================================================

#endif
