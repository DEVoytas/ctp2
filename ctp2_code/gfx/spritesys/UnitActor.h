//----------------------------------------------------------------------------
//
// Project      : Call To Power 2
// File type    : C++ source
// Description  : Unit actor
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
// _DEBUG
// - Generates debug information when set.
//
// _ACTOR_DRAW_OPTIMIZATION
//
//----------------------------------------------------------------------------
//
// Modifications from the original Activision code:
//
// - Unit stacking indications and special indecations are placed according
//   their size. (9-Feb-2008 Martin G�hmann)
//
//----------------------------------------------------------------------------

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif
#ifndef __UNITACTOR_H__
#define __UNITACTOR_H__

#include <deque>

class UnitActor;

#include "gfx/spritesys/Action.h"             // Action, GAME_ACTION
#include "gfx/spritesys/Actor.h"              // Actor
#include "gfx/spritesys/Anim.h"               // Anim
#include "os/include/ctp2_inttypes.h"      // sintN, uintN
#include "gs/world/MapPoint.h"           // MapPoint
#include "gfx/spritesys/SpriteGroup.h"        // GROUPTYPE, LOADTYPE
#include "gs/gameobj/Unit.h"               // SPECATTACK, Unit
#include "gfx/spritesys/UnitSpriteGroup.h"    // UNITACTION

class aui_Surface;
class CivArchive;
class SpriteState;
// BOOL, POINT, RECT

#if 0
#include "gfx/gfx_utils/pixelutils.h"
#include "gs/gameobj/XY_Coordinates.h"
#include "gs/world/World.h"
#include "ui/aui_common/tech_wllist.h"

class SpriteGroup;
class ProjectileActor;
class EffectActor;
class ActorPath;
#endif

class UnitActor : public Actor
{
public:
	UnitActor(SpriteStatePtr ss, Unit id, sint32 type, const MapPoint &pos,
			  sint32 owner, BOOL isUnseenCellActor, double visionRange,
			  sint32 citySprite);
	UnitActor(CivArchive &archive);

	~UnitActor();

	void			GetIDAndType
    (
        sint32              owner,
        SpriteStatePtr      ss,
        Unit                id,
        sint32              unitType,
        MapPoint const &    pos,
        sint32 *            spriteID,
        GROUPTYPE *         groupType,
        sint32              citySprite = CTPRecord::INDEX_INVALID
    ) const;

	void			AddVision(void);
	void			RemoveVision(void);
	void			PositionActor(MapPoint &pos);
	void			Hide(void);
	void			Show(void);

	void			Initialize(void);

	void			ChangeImage(SpriteStatePtr ss, sint32 type, Unit id);
	void			ChangeType(SpriteStatePtr ss, sint32 type, Unit id, BOOL updateVision);

	void			SetSize(sint32 size) { m_size = size; }
	sint32			GetSize(void) const { return m_size; }

	virtual void	Process(void);
	void			DumpAllActions(void);
	void			EndTurnProcess(void);
	ActionPtr	WillMorph(void) const;
	ActionPtr	WillDie(void) const;
  void			AddAction(ActionPtr actionObj) override;
	void			GetNextAction(bool isVisible = true);
	void			AddIdle(bool NoIdleJustDelay = false);
	void			ActionQueueUpIdle(bool NoIdleJustDelay = false);

	Anim *CreateAnim(UNITACTION action);
	Anim *MakeFakeDeath(void);
	Anim *MakeFaceoff(void);

	bool			HasThisAnim(UNITACTION action) const
	{
		return m_unitSpriteGroup && m_unitSpriteGroup->GetAnim((GAME_ACTION) action);
	}

	void			DrawFortified(bool fogged);
	void			DrawFortifying(bool fogged);
	void			DrawCityWalls(bool fogged);
	void			DrawForceField(bool fogged);
	void			DrawCityImprovements(bool fogged); //emod

	bool			Draw(bool fogged = FALSE);
	void			DrawHerald(void);
	void			DrawSelectionBrackets(void);
	void			DrawHealthBar(void);
	void			DrawStackingIndicator(sint32 &x, sint32 &y, sint32 stackSize);
	void			DrawIndicators(sint32 &x, sint32 &y, sint32 stackSize);
	void			DrawSpecialIndicators(sint32 &x, sint32 &y, sint32 stackSize);
	void			DrawText(sint32 x, sint32 y, MBCHAR *unitText);

	void			DrawDirect(aui_Surface *surf, sint32 x, sint32 y, double scale);

	bool			IsAnimating(void) const;

	MapPoint		GetPos(void) const { return m_pos; }
	void			SetPos(MapPoint pnt) { m_pos = pnt; }
	MapPoint		GetSavedPos(void) const { return m_savePos; }
	void			SetSavedPos(MapPoint pnt) { m_savePos = pnt; }
	void            GetPixelPos(sint32 &x, sint32 &y) const { x = m_x; y = m_y; }

	sint32			GetFacing(void) const { return m_facing; }

	uint16			GetWidth(void) const;
	uint16			GetHeight(void) const;

	uint32		    GetUnitID(void) const { return m_unitID.m_id; }
	sint32			GetUnitDBIndex(void) const { return m_unitDBIndex; }

	void			SetPlayerNum(sint32 playerNum) { m_playerNum = playerNum; }
	sint32			GetPlayerNum(void) const { return m_playerNum;}

	sint32			GetNextPop(void) const { return m_nextPop;}

	bool			HasDeath(void) const { return m_unitSpriteGroup->HasDeath(); }
	bool			HasDirectional(void) { return m_unitSpriteGroup->HasDirectional(); }

	void			SetUnitVisibility(uint32 val) { m_unitSaveVisibility = m_unitVisibility = val; }
	void			SetUnitVisibility(uint32 val, BOOL bval) { m_unitSaveVisibility = m_unitVisibility; m_unitVisibility = val; m_bVisSpecial = TRUE; }

	void			SetUnitVisibility() { m_bVisSpecial = FALSE; }
	uint32			GetUnitVisibility(void) const { return m_unitVisibility; }
	uint32			GetUnitSavedVisibility(void) const { return m_unitSaveVisibility; }

	BOOL			GetVisSpecial(void) const { return m_bVisSpecial; }
	void			SetVisSpecial(BOOL val) { m_bVisSpecial = val; }

	double			GetUnitVisionRange(void) const { return m_unitVisionRange; }
	void            SetUnitVisionRange(double range) { m_unitVisionRange = range; }
	void            SetNewUnitVisionRange(double range) { m_newUnitVisionRange = range; }

	void			SetNeedsToDie(BOOL val) { m_needsToDie = val; }
	BOOL			GetNeedsToDie(void) const { return m_needsToDie; }

	void			SetNeedsToVictor(BOOL val) { m_needsToVictor = val; }
	BOOL			GetNeedsToVictor(void) const { return m_needsToVictor; }

	void			SetKillNow(void) { m_killNow = TRUE; }
	BOOL			GetKillNow(void) const { return m_killNow; }

  void			SetRevealedActors(UnitActor **revealedActors);
  void			SaveRevealedActors(UnitActor **revealedActors);
	UnitActor		**GetRevealedActors(void) const { return m_revealedActors; }

  void			SetMoveActors(UnitActor **moveActors, sint32 numOActors);
	UnitActor		**GetMoveActors(void) const { return m_moveActors; }
	sint32			GetNumOActors(void) const { return m_numOActors; }

	BOOL			HiddenUnderStack(void) const { return m_hiddenUnderStack; }
	void			SetHiddenUnderStack(BOOL val) { m_hiddenUnderStack = val; }

	void			SetIsTransported(sint32 val) { m_isTransported = val; }
	sint32			GetIsTransported() const { return m_isTransported; }

	void			GetBoundingRect(RECT *rect) const;

	sint32			GetHoldingCurAnimPos(UNITACTION action) const { return m_holdingCurAnimPos[action]; }
	sint32			GetHoldingCurAnimDelayEnd(UNITACTION action) const { return m_holdingCurAnimDelayEnd[action]; }
	sint32			GetHoldingCurAnimElapsed(UNITACTION action) const { return m_holdingCurAnimElapsed[action]; }
	sint32			GetHoldingCurAnimLastFrameTime(UNITACTION action) const { return m_holdingCurAnimLastFrameTime[action]; }
	sint32			GetHoldingCurAnimSpecialDelayProcess(UNITACTION action) const { return m_holdingCurAnimSpecialDelayProcess; }

	LOADTYPE		GetLoadType(void) const;

	void			FullLoad(UNITACTION action);
	void			DumpFullLoad(void);

	void			SetIsFortified(BOOL fort) { m_isFortified = fort; }
	void			SetIsFortifying(BOOL fort) { m_isFortifying = fort; }
	BOOL			IsFortified(void) const { return m_isFortified; }
	BOOL			IsFortifying(void) const { return m_isFortifying; }

	void			SetHasCityWalls(BOOL has) { m_hasCityWalls = has; }
	void			SetHasForceField(BOOL has) { m_hasForceField = has; }
	BOOL			HasCityWalls(void) const { return m_hasCityWalls;}
	BOOL			HasForceField(void) const { return m_hasForceField; }

	void			SetHealthPercent(double p) { m_healthPercent = p;}
	double			GetHealthPercent(void) const { return m_healthPercent; }

	void			SetTempStackSize(sint32 i) { m_tempStackSize = i; }
	sint32			GetTempStackSize(void) const { return m_tempStackSize; }

	BOOL			HitTest(POINT mousePt);





	void			AddActiveListRef(void) { m_activeListRef++; }
	sint32			ReleaseActiveListRef(void) { return --m_activeListRef;}
	sint32			GetActiveListRef(void) const { return m_activeListRef; }

	void			Serialize(CivArchive &archive);

#ifdef _DEBUG
	void			DumpActor(void);
#endif
	sint32          m_refCount;

	bool			ActionMove	       (ActionPtr actionObj) override;
	bool			ActionAttack       (ActionPtr actionObj, sint32 facing);
	bool			ActionSpecialAttack(ActionPtr actionObj, sint32 facing);
	bool      TryAnimation       (ActionPtr actionObj, UNITACTION action);

	void			TerminateLoopingSound	(uint32 sound_type);
	void			AddSound				(uint32 sound_type, sint32 sound_id);
	void			AddLoopingSound			(uint32 sound_type, sint32 sound_id);

	void            HackSetSpriteID(sint32 spriteID) { m_spriteID = spriteID; }

protected:
	MapPoint			m_pos;
	MapPoint			m_savePos;
	Unit				m_unitID;
	sint32				m_unitDBIndex;
	sint32				m_playerNum;

	sint32              m_nextPop; //PFT 29 mar 05, show # turns until city next grows a pop

	UnitSpriteGroup		*m_unitSpriteGroup;
	LOADTYPE			m_loadType;

	sint32				m_facing;
	sint32				m_lastMoveFacing;
	sint32				m_frame;
	uint16				m_transparency;

	UNITACTION			m_curUnitAction;

	RECT				m_heraldRect;

	uint32				m_unitVisibility;
	uint32				m_unitSaveVisibility;

	BOOL				m_directionalAttack;
 	BOOL				m_needsToDie;
 	BOOL				m_needsToVictor;
	BOOL				m_killNow;
	double				m_unitVisionRange;
	double              m_newUnitVisionRange;

	sint32				m_numRevealedActors;
	UnitActor			**m_revealedActors;
	sint32				m_numSavedRevealedActors;
	UnitActor			**m_savedRevealedActors;

	BOOL				m_bVisSpecial;

	UnitActor			**m_moveActors;
	sint32				m_numOActors;
	BOOL				m_hidden;
	BOOL				m_hiddenUnderStack;
	sint32				m_isTransported;

	sint32				m_holdingCurAnimPos[UNITACTION_MAX];
	sint32				m_holdingCurAnimDelayEnd[UNITACTION_MAX];
	sint32				m_holdingCurAnimElapsed[UNITACTION_MAX];
	sint32				m_holdingCurAnimLastFrameTime[UNITACTION_MAX];
	sint32				m_holdingCurAnimSpecialDelayProcess;

	sint32				m_size;
	BOOL                m_isUnseenCellActor;

	GROUPTYPE			m_type;
	sint32				m_spriteID;

	BOOL				m_isFortified;
	BOOL				m_isFortifying;
	BOOL				m_hasCityWalls;
	BOOL				m_hasForceField;

	uint32				m_shieldFlashOnTime;
	uint32				m_shieldFlashOffTime;

	sint32				m_activeListRef;
	double				m_healthPercent;
	sint32				m_tempStackSize;

#ifdef _ACTOR_DRAW_OPTIMIZATION

	sint32				m_oldFacing;
	BOOL				m_oldIsFortified;
	BOOL				m_oldIsFortifying;
	BOOL				m_oldHasCityWalls;
	BOOL				m_oldHasForceField;
	BOOL				m_oldDrawShield;
	BOOL				m_oldDrawSelectionBrackets;
	uint16				m_oldFlags;

#endif
};

#endif
