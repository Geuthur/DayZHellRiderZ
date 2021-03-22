class HRZ_ActionAttachCodeLock: ActionAttach
{
	Object c_Target;

	void HRZ_ActionAttachCodeLock()
	{
	}

	override void CreateConditionComponents() 
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}
		
	override string GetText()
	{
		return "Codeschloss Anbringen";
	}
	
	override ActionData CreateActionData()
	{
		AttachActionData action_data = new AttachActionData;
		return action_data;
	}
	
	override bool SetupAction( PlayerBase player, ActionTarget target, ItemBase item, out ActionData action_data, Param extra_data = NULL )
	{
		ref InventoryLocation il = new InventoryLocation;
		if (!GetGame().IsMultiplayer() || GetGame().IsClient())
		{
			Fence fence = Fence.Cast( target.GetObject() );
			
			if( !fence.GetInventory().FindFirstFreeLocationForNewEntity( item.GetType(), FindInventoryLocationType.ATTACHMENT, il ) )
				return false;
		}
			
		if ( super.SetupAction( player, target, item, action_data, extra_data))
		{
			if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
			{
				AttachActionData action_data_a = AttachActionData.Cast( action_data );
				action_data_a.m_AttSlot = il.GetSlot();
			}
			return true;
		}
		return false;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		EntityAI targetObject 	= EntityAI.Cast( target.GetObject() );
		EntityAI targetParent 	= EntityAI.Cast( target.GetParent() );
		HRZ_CodeLock hrz_Lock 		= HRZ_CodeLock.Cast( item );
		Fence fence				= Fence.Cast( targetObject );
		
		if ( fence && hrz_Lock )
		{
			if ( fence.GetInventory() && fence.GetInventory().CanAddAttachment( hrz_Lock ) )
			{
				return true;
			}
		}	
		return false;
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		AttachActionData action_data_a 	= AttachActionData.Cast(action_data);
		Fence fence 					= Fence.Cast( action_data_a.m_Target.GetObject() );;

		if ( fence && action_data_a.m_MainItem )
		{
			action_data_a.m_Player.PredictiveTakeEntityToTargetAttachmentEx( fence, action_data_a.m_MainItem, action_data_a.m_AttSlot );
		}
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		
		AttachActionData action_data_a 	= AttachActionData.Cast(action_data);
		Fence fence						= Fence.Cast( action_data_a.m_Target.GetObject());
		
		if ( !fence ) return;

		GetRPCManager().SendRPC( "HRZLockRPC_Client", "HRZ_ShowSetCodeUI", new Param1< Object >( fence ), true, action_data.m_Player.GetIdentity() );

		if (GetGame().IsMultiplayer())
			return;
		
		if ( fence && action_data_a.m_MainItem )
		{
			action_data_a.m_Player.PredictiveTakeEntityToTargetAttachmentEx( fence, action_data_a.m_MainItem, action_data_a.m_AttSlot );
		}

		return;
	}
}