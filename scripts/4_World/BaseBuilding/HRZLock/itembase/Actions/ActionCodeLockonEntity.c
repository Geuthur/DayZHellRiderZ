class HRZ_ActionCodeLockonEntity : ActionInteractBase
{
	Object currTarget = NULL;
	string lockText;
	bool useProxies;

	void HRZ_ActionCodeLockonEntity()
	{
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}
	
	override bool IsInstant()
	{
		return true;
	}

	override string GetText()
	{
		return lockText;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		Object targetObject = target.GetObject();
		Fence fence 		= Fence.Cast( targetObject );
		HRZ_CodeLock hrz_Lock;
		
		if ( fence )
		{
			string selection = fence.GetActionComponentName( target.GetComponentIndex() );
			if ( selection == "wall_interact" )
				Class.CastTo( hrz_Lock, fence.GetHRZLock() );
		}

		// Make sure hrz_Lock isn't NULL
		if ( hrz_Lock )
		{
			if ( hrz_Lock.GetLockState() )
				lockText = "Password Eingeben";
			else
				lockText = "Setze Password";

			return true;
		}
		
		return false;
	}
	
	override void Start( ActionData action_data )
	{
		PlayerIdentity p_Identity 	= action_data.m_Player.GetIdentity();
		Object targetObject 		= action_data.m_Target.GetObject();
		Fence fence					= Fence.Cast( targetObject );
		HRZ_CodeLock hrz_Lock;
		
		if ( fence )
		{
			Class.CastTo( hrz_Lock, fence.GetHRZLock() );
		}

		// Make sure hrz_Lock isn't NULL
		if ( hrz_Lock )
		{
			if ( hrz_Lock.GetLockState() )
			{
				GetRPCManager().SendRPC( "HRZLockRPC_Client", "HRZ_ShowEnterCodeUI", new Param3< EntityAI, Object, HRZ_CodeLock >( action_data.m_Player, fence, hrz_Lock ), true, p_Identity );
				return;
			}
			
			GetRPCManager().SendRPC( "HRZLockRPC_Client", "HRZ_ShowSetCodeUI", new Param1< Object >( fence ), true, p_Identity );
			return;
		}
	}	
}