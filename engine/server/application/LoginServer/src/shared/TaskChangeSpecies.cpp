// ======================================================================
//
// TaskChangeSpecies.cpp
// copyright (c) 2001 Sony Online Entertainment
//
// ======================================================================

#include "FirstLoginServer.h"
#include "TaskChangeSpecies.h"
#include "LoginServer.h"
#include "DatabaseConnection.h"
#include "serverNetworkMessages/TransferCharacterData.h"
#include "serverNetworkMessages/TransferCharacterDataArchive.h"
#include "sharedDatabaseInterface/DbSession.h"
#include "sharedNetworkMessages/GenericValueTypeMessage.h"

// ======================================================================

TaskChangeSpecies::TaskChangeSpecies(uint32 clusterId, const NetworkId &characterId, const Unicode::String &newSpeciesTemplate, const TransferCharacterData * requestData) :
		TaskRequest(),
		m_clusterId(clusterId),
		m_characterId(characterId),
		m_newSpeciesTemplate(newSpeciesTemplate),
		m_success(false),
		m_requestData(0)
{
	if(requestData)
	{
		m_requestData = new TransferCharacterData(*requestData);
	}
}

// ----------------------------------------------------------------------

TaskChangeSpecies::~TaskChangeSpecies()
{
	delete m_requestData;
}

// ----------------------------------------------------------------------

bool TaskChangeSpecies::process(DB::Session *session)
{
	ChangeSpeciesQuery qry;
	qry.cluster_id=m_clusterId; //lint !e713 loss of precision
	qry.character_id=m_characterId;
	qry.new_species_template = m_newSpeciesTemplate;
	
	m_success = session->exec(&qry); 
	
	qry.done();
	return m_success;
}

// ----------------------------------------------------------------------

void TaskChangeSpecies::onComplete()
{
	if(m_requestData)
	{
		m_requestData->setIsValidName(m_success);
		GenericValueTypeMessage<TransferCharacterData> reply("TransferChangeSpeciesReplyFromLoginServer", *m_requestData);
		LoginServer::getInstance().sendToCluster(m_clusterId, reply);
	}
}

// ======================================================================

TaskChangeSpecies::ChangeSpeciesQuery::ChangeSpeciesQuery() :
		Query(),
		cluster_id(),
		character_id(),
		new_species_template()
{
}

// ----------------------------------------------------------------------

void TaskChangeSpecies::ChangeSpeciesQuery::getSQL(std::string &sql)
{
	sql = std::string("begin ")+DatabaseConnection::getInstance().getSchemaQualifier()+"login.change_species(:cluster_id, :character_id, :new_species_template); end;";
 	// DEBUG_REPORT_LOG(true, ("TaskChangeSpecies SQL: %s\n", sql.c_str()));
}

// ----------------------------------------------------------------------

bool TaskChangeSpecies::ChangeSpeciesQuery::bindParameters()
{
	if (!bindParameter(cluster_id)) return false;
	if (!bindParameter(character_id)) return false;
	if (!bindParameter(new_species_template)) return false;
	return true;
}

// ----------------------------------------------------------------------

bool TaskChangeSpecies::ChangeSpeciesQuery::bindColumns()
{
	return true;
}

// ----------------------------------------------------------------------

DB::Query::QueryMode TaskChangeSpecies::ChangeSpeciesQuery::getExecutionMode() const
{
	return MODE_PROCEXEC;
}

// ======================================================================
