modded class ActionDigOutStashCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(5.5);
	}
};

modded class ActionDigInStashCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(5.5);
	}
};

modded class ActionDigOutStash extends ActionContinuousBase
{
    HRZ_PluginAdminLog m_DigOutStash;

	override void OnFinishProgressServer( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		EntityAI targetEntity = EntityAI.Cast(targetObject);
		UndergroundStash target_stash;
		if (!targetEntity)
		{
			Error("ActionDigStash - Cannot get inventory of targetObject=" + targetObject);
			return;
		}
		
		InventoryLocation target_IL = new InventoryLocation;
		if (!targetEntity.GetInventory().GetCurrentInventoryLocation(target_IL))
		{
			Error("ActionDigStash: Cannot get inventory location of targetObject=" + targetObject);
			return;
		}
		
		// Dig out of stash
		if ( Class.CastTo(target_stash, targetEntity) )
		{
			ItemBase chest = target_stash.GetStashedItem();
			
			if (chest)
			{
				m_DigOutStash = HRZ_PluginAdminLog.Cast( GetPlugin(HRZ_PluginAdminLog) );
				m_DigOutStash.HRZ_DigOutStash(action_data.m_Player, chest);
				
				DigOutStashLambda lambda(target_stash, "", action_data.m_Player);
				action_data.m_Player.ServerReplaceItemWithNew(lambda);
			}
			else
				g_Game.ObjectDelete( target_stash );
		}

		//Apply tool damage
		MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, 17);		
		
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
	
	}
}


modded class ActionDigInStash extends ActionContinuousBase
{
    HRZ_PluginAdminLog m_DigInStash;

	override void OnFinishProgressServer( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		EntityAI targetEntity = EntityAI.Cast(targetObject);
		UndergroundStash target_stash;
		if (!targetEntity)
		{
			Error("ActionDigStash - Cannot get inventory of targetObject=" + targetObject);
			return;
		}
		
		InventoryLocation target_IL = new InventoryLocation;
		if (!targetEntity.GetInventory().GetCurrentInventoryLocation(target_IL))
		{
			Error("ActionDigStash: Cannot get inventory location of targetObject=" + targetObject);
			return;
		}
		
		ItemBase stashed_item;
		UndergroundStash stash;
		vector pos = targetEntity.GetPosition();
					
		Class.CastTo(stashed_item,  targetEntity );
		Class.CastTo(stash,  GetGame().CreateObjectEx("UndergroundStash", pos, ECE_PLACE_ON_SURFACE) );
		  
		if ( stash )
		{
			stash.PlaceOnGround();
			
			if (GameInventory.LocationCanRemoveEntity(target_IL))
			{
				action_data.m_Player.ServerTakeEntityToTargetCargo(stash, stashed_item);
			}
			else
				Print("ActionDigStash: Cannot remove targetObject=" + targetObject + " obj from current location=" + InventoryLocation.DumpToStringNullSafe(target_IL));
		}
		else
		{
			Error("ERROR! ActionDigStash: Stash not spawned!");
		}
		
		//Apply tool damage
		MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, 17);				
		
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
		
		m_DigInStash = HRZ_PluginAdminLog.Cast( GetPlugin(HRZ_PluginAdminLog) );
		m_DigInStash.HRZ_DigInStash(action_data.m_Player, stashed_item);
	}
}

