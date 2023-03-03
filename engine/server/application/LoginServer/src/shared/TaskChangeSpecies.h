// ======================================================================
//
// TaskChangeSpecies.h
// copyright (c) 2001 Sony Online Entertainment
//
// ======================================================================

#ifndef INCLUDED_TaskChangeSpecies_H
#define INCLUDED_TaskChangeSpecies_H

// ======================================================================

#include "sharedDatabaseInterface/Bindable.h"
#include "sharedDatabaseInterface/BindableNetworkId.h"
#include "sharedDatabaseInterface/DbQuery.h"
#include "sharedDatabaseInterface/DbTaskRequest.h"

class TransferCharacterData;

// ======================================================================

class TaskChangeSpecies : public DB::TaskRequest
{
  public:
	TaskChangeSpecies(uint32 clusterId, const NetworkId &characterId, const Unicode::String &newSpeciesTemplate, const TransferCharacterData * requestData);
	~TaskChangeSpecies();
  
  public:
	virtual bool process    (DB::Session *session);
	virtual void onComplete ();

  private:
	TaskChangeSpecies(); // disabled default constructor
	class ChangeSpeciesQuery : public DB::Query
	{
	  public:
		ChangeSpeciesQuery();

		DB::BindableLong         cluster_id; //lint !e1925 // public data member
		DB::BindableNetworkId    character_id; //lint !e1925 // public data member
		DB::BindableString<127>  new_species_template; //lint !e1925 // public data member

		virtual void getSQL                (std::string &sql);
		virtual bool bindParameters        ();
		virtual bool bindColumns           ();
		virtual QueryMode getExecutionMode () const;

	  private: //disable
		ChangeSpeciesQuery               (const ChangeSpeciesQuery&);
		ChangeSpeciesQuery &operator=    (const ChangeSpeciesQuery&);
	};

  private:
	uint32           m_clusterId;
	NetworkId        m_characterId;
	Unicode::String  m_newSpeciesTemplate;
	bool             m_success;
	TransferCharacterData *  m_requestData;
};

// ======================================================================

#endif
