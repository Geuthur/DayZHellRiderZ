class HRZ_ActionDestroyCodeLockCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime( UATimeSpent.DEFAULT_DESTROY );
	}
};

class HRZ_ActionDestroyCodeLock: ActionContinuousBase
{	
	Fence c_TargetFence = NULL;

	void HRZ_ActionDestroyCodeLock()
	{
		m_CallbackClass = HRZ_ActionDestroyCodeLockCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_MEDIUM;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

/* 	override int GetType()
	{
		return ACTION_CUT_CODELOCK;
	} */

	override string GetText()
	{
		return "Hacke Codeschloss";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		Fence fence			= Fence.Cast( targetObject );
		HRZ_CodeLock hrz_Lock;

		if ( fence )
		{
			string selection = targetObject.GetActionComponentName( target.GetComponentIndex() );
			if ( selection == "wall_interact" )
				Class.CastTo( hrz_Lock, fence.GetHRZLock() );
		}

		if ( hrz_Lock )
		{
			if ( !c_TargetFence || c_TargetFence != fence )
			{
				c_TargetFence = fence;
				GetRPCManager().SendRPC( "HRZLockRPC_Server", "HRZ_GetConfig", NULL, true, player.GetIdentity() );
			}

			if ( g_HRZLockRPCManager.m_CanHackLock )
				return true;
		}
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{	
		super.OnFinishProgressServer( action_data );
		
		Object targetObject = action_data.m_Target.GetObject();
		Fence fence			= Fence.Cast( targetObject );
		HRZ_CodeLock hrz_Lock;

		if ( !g_HRZLockRPCManager.m_CanHackLock )
		{
			return;
		}

		if ( fence )
		{
			Class.CastTo( hrz_Lock, fence.GetHRZLock() );
		}

		if ( hrz_Lock )
			hrz_Lock.UnlockServer( action_data.m_Player, fence );
	}
};

// Make sure it doesn't call the CodeLock as a CombinationLock and allow it to be cut off regardless.
modded class ActionDestroyCombinationLock: ActionContinuousBase
{	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		ItemBase entity = ItemBase.Cast( target.GetObject() );
		HRZ_CodeLock hrz_Lock = HRZ_CodeLock.Cast( entity.GetHRZLock() );

		if ( hrz_Lock ) return false;
		
		return super.ActionCondition( player, target, item );
	}
};

// Make sure the tools that are supposed to be able to cut locks off, have the action.
modded class ElectronicRepairKit extends ToolBase
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction( HRZ_ActionDestroyCodeLock );
	}
}