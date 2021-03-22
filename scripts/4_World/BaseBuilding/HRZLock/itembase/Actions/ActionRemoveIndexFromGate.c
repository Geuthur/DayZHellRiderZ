// Removes 'Next Dial' from CodeLocks on Gates
modded class ActionNextCombinationLockDialOnTarget: ActionInteractBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if (!target.GetObject())
			return false;
		
		HRZ_CodeLock hrz_Lock = HRZ_CodeLock.Cast( target.GetObject() );
		CombinationLock lock = CombinationLock.Cast( target.GetObject() );
		if ( lock && lock.GetHierarchyParent() && Fence.Cast(lock.GetHierarchyParent()) )
		{
			if ( hrz_Lock ) return false;
			ConstructionActionData construction_action_data = player.GetConstructionActionData();
			construction_action_data.SetCombinationLock( lock );
			
			return true;
		}
		
		return false;
	}
/*	Old Code 1.08
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		Object targetObject = target.GetObject();
		if ( targetObject && targetObject.CanUseConstruction() )
		{
			Fence fence = Fence.Cast( targetObject );
			HRZ_CodeLock hrz_Lock = HRZ_CodeLock.Cast( fence.GetHRZLock() );

			if ( hrz_Lock ) return false;
			
			return super.ActionCondition( player, target, item );
		}
		
		return false;
	}*/
};

// Removes the dial index from the Code Lock
modded class ActionDialCombinationLockOnTarget: ActionContinuousBase
{
	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		Object targetObject = target.GetObject();
		if ( targetObject && targetObject.CanUseConstruction() )
		{
			Fence fence = Fence.Cast( targetObject );
			HRZ_CodeLock hrz_Lock = HRZ_CodeLock.Cast( fence.GetHRZLock() );

			if ( hrz_Lock ) return false;
		}

        return super.ActionCondition( player, target, item );
	}
	/* 1.10 Version
	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{ 
		Object targetObject = target.GetObject();
		if ( targetObject && targetObject.CanUseConstruction() )
		{
		Fence fence = Fence.Cast( targetObject );
  
			if ( fence && fence.IsLocked() )
			{
				string selection = fence.GetActionComponentName( target.GetComponentIndex() );
			
				if ( selection == "wall_interact" )
				{
				ConstructionActionData construction_action_data = player.GetConstructionActionData();
				construction_action_data.SetCombinationLock( fence.GetCombinationLock() );
	
				return true;
				}
			}
		}
		return false;
	}*/
}