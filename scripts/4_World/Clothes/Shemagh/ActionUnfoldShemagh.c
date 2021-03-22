class HRZ_ActionUnfoldShemagh : ActionSingleUseBase
{
	void HRZ_ActionUnfoldShemagh ()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_PICKUP_HANDS;
	}

	override void CreateConditionComponents ()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
		return "Zerlege Banditenmaske";
	}

	override bool HasTarget () { return false; }

	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (item)
			return true;
		return false;
	}

	override bool ActionConditionContinue ( ActionData action_data ) { return true; }

	override void OnExecuteClient ( ActionData action_data )
	{
		ClearInventoryReservation(action_data);
	}

	override void OnExecuteServer ( ActionData action_data )
	{
		if ( !GetGame().IsMultiplayer() )
			ClearInventoryReservation(action_data);

		ItemBase old_item = action_data.m_MainItem;
		if (old_item.ConfigIsExisting("color"))
		{
			string str = "HRZ_Shemagh_" + old_item.ConfigGetString("color");
			TurnItemIntoItemLambda lambda = new TurnItemIntoItemLambda(action_data.m_MainItem, str, action_data.m_Player);
			lambda.SetTransferParams(true, true, true, false, 1);
			action_data.m_Player.ServerReplaceItemInHandsWithNew(lambda);
		}

	}
};
