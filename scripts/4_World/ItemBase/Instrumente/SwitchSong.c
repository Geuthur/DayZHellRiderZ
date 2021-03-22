class HRZ_ActionSwitchSong : ActionContinuousBase
{
	string str;
	
	void HRZ_ActionSwitchSong ()
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
		return "Nächster Song";
	}

	override bool HasTarget () 
	{ 
		return false; 
	}

	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
	HRZ_Instruments_Base radio;
	Class.CastTo(radio, item);
			if (radio.!IsPlaying()) 
			{
				return true;
			}
		return false;
	}

	override bool ActionConditionContinue ( ActionData action_data ) 
	{ 
		return true; 
	}

	override void OnExecuteClient ( ActionData action_data )
	{
		ClearInventoryReservation(action_data);
	}
	
	/*
	string GetNextSong(string Song)
    {
        if (Song == "")
        {
            return "";
        }
        Song = "HRZ_Gitarre_" + Song;
		for ( int i = 0; i < InsrumentsSong.Count(); ++i ) {
            if (Song == InsrumentsSong[i]) {
                return Song;
            }
        }
        return "";        
    }
	*/

	override void OnExecuteServer ( ActionData action_data )
	{
		if ( !GetGame().IsMultiplayer() )
			ClearInventoryReservation(action_data);
		
			ItemBase old_item = action_data.m_MainItem;
			switch (old_item.ClassName()) {
					case "HRZ_Gitarre" : { str = "HRZ_Gitarre2";} break;
					case "HRZ_Gitarre2" : { str = "HRZ_Gitarre3";} break;
					case "HRZ_Gitarre3" : { str = "HRZ_Gitarre4";} break;
					case "HRZ_Gitarre4" : { str = "HRZ_Gitarre5";} break;
					case "HRZ_Gitarre5" : { str = "HRZ_Gitarre";} break;
			}
			//Print(str);
			TurnItemIntoItemLambda lambda = new TurnItemIntoItemLambda(action_data.m_MainItem, str, action_data.m_Player);
			lambda.SetTransferParams(true, true, true, false, 1);
			action_data.m_Player.ServerReplaceItemInHandsWithNew(lambda);
	}
};
