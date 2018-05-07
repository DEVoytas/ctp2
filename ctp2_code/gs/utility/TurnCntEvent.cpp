//----------------------------------------------------------------------------
//
// Project      : Call To Power 2
// File type    : C++ source
// Description  : The begin turn event, that is executed on every new turn.
// Id           : $Id$
//
//----------------------------------------------------------------------------
//
// Disclaimer
//
// THIS FILE IS NOT GENERATED OR SUPPORTED BY ACTIVISION.
//
// This material has been developed at apolyton.net by the Apolyton CtP2
// Source Code Project. Contact the authors at ctp2source@apolyton.net.
//
//----------------------------------------------------------------------------
//
// Compiler flags
//
// - None
//
//----------------------------------------------------------------------------
//
// Modifications from the original Activision code:
//
// - Added HotSeat and PBEM human-human diplomacy support. (17-Oct-2007 Martin G�hmann)
// - Added Event for handling HotSeat and PBEM meassage and PBEM saving,
//   so that PBEM saving can be done after all events have been executed. (14-Nov-2007 Martin G�hmann)
// - Moved the startegic state calculation before everthing else, so that
//   each turn has the right startegy even after a reload. (13-Aug-2008 Martin G�hmann)
//
//----------------------------------------------------------------------------

#include "ctp/c3.h"
#include "gs/gameobj/Events.h"
#include "gs/utility/TurnCntEvent.h"
#include "gs/utility/TurnCnt.h"
#include "gs/events/GameEventUser.h"

#include "gs/gameobj/Player.h"

#include "gs/database/profileDB.h"
#include "gfx/spritesys/director.h"
#include "net/general/network.h"
#include "ai/ctpai.h"
#include "gs/utility/newturncount.h"

#include "ai/diplomacy/Diplomat.h"

STDEHANDLER(BeginTurnEvent)
{
	sint32 player;
	sint32 round;
	if(!args->GetPlayer(0, player))
	{
		return GEV_HD_Continue;
	}

	if(!args->GetInt(0, round))
	{
		return GEV_HD_Continue;
	}

	Assert(g_player[player] != NULL);

	g_player[player]->m_current_round = round;

	g_director->NextPlayer();

	if(g_theProfileDB->IsAIOn() && (!g_network.IsClient()))
	{
		g_gevManager->AddEvent(GEV_INSERT_Tail, GEV_AiBeginMapAnalysis,
		                       GEA_Player,      player,
		                       GEA_End
		                      );
	}

	CtpAi::BeginDiplomacy(player, round);

	if(g_theProfileDB->IsAIOn() && (!g_network.IsClient()))
	{
		g_gevManager->AddEvent(GEV_INSERT_Tail, GEV_AiBeginTurn,
		                       GEA_Player,      player,
		                       GEA_End
		                      );
	}

	g_player[player]->BeginTurn();

	g_gevManager->AddEvent(GEV_INSERT_Tail, GEV_ResumeEmailAndHotSeatDiplomacy,
	                       GEA_Player,      player,
	                       GEA_End
	                      );

	return GEV_HD_Continue;
}

STDEHANDLER(ResumeEmailAndHotSeatDiplomacy)
{
	sint32 player;
	if(!args->GetPlayer(0, player))
	{
		return GEV_HD_Continue;
	}

	Diplomat::ExecuteDelayedNegotiations(player);

	return GEV_HD_Continue;
}

STDEHANDLER(SendEmailAndHotSeatMessage)
{
	// So that the following code can be delayed until all events have been handled.
	g_turn->SendNextPlayerMessageEvent();

	return GEV_HD_Continue;
}

void turncountevent_Initialize()
{
	g_gevManager->AddCallback(GEV_BeginTurn, GEV_PRI_Primary, &s_BeginTurnEvent);
	g_gevManager->AddCallback(GEV_ResumeEmailAndHotSeatDiplomacy, GEV_PRI_Primary, &s_ResumeEmailAndHotSeatDiplomacy);
	g_gevManager->AddCallback(GEV_SendEmailAndHotSeatMessage, GEV_PRI_Primary, &s_SendEmailAndHotSeatMessage);
}

void turncountevent_Cleanup()
{
}
