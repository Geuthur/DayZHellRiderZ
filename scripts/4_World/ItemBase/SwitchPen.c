class HRZ_ActionSwitchPen : ActionContinuousBase
{
	string str;
	
	void HRZ_ActionSwitchPen ()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_PICKUP_HANDS;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		m_FullBody = false;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}

	override void CreateConditionComponents ()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
		return "Nächste Farbe";
	}

	override bool HasTarget () 
	{ 
		return false; 
	}

	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return true;
	}

	override bool ActionConditionContinue ( ActionData action_data ) 
	{ 
		return true; 
	}

	override void OnExecuteClient ( ActionData action_data )
	{
		ClearInventoryReservation(action_data);
	}

	override void OnExecuteServer ( ActionData action_data )
	{
		if ( !GetGame().IsMultiplayer() )
			ClearInventoryReservation(action_data);
		
			ItemBase old_item = action_data.m_MainItem;
			switch (old_item.ClassName()) {
					case "HRZ_Pen_Black" : { str = "HRZ_Pen_Red";} break;
					case "HRZ_Pen_Red" : { str = "HRZ_Pen_Blue";} break;
					case "HRZ_Pen_Blue" : { str = "HRZ_Pen_Green";} break;
					case "HRZ_Pen_Green" : { str = "HRZ_Pen_Pink";} break;
					case "HRZ_Pen_Pink" : { str = "HRZ_Pen_Turkis";} break;
					case "HRZ_Pen_Turkis" : { str = "HRZ_Pen_Orange";} break;
					case "HRZ_Pen_Orange" : { str = "HRZ_Pen_Black";} break;
			}
			//Print(str);
			TurnItemIntoItemLambda lambda = new TurnItemIntoItemLambda(action_data.m_MainItem, str, action_data.m_Player);
			lambda.SetTransferParams(true, true, true, false, 1);
			action_data.m_Player.ServerReplaceItemInHandsWithNew(lambda);
	}
};