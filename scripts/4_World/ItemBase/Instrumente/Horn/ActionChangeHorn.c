class HRZ_ActionChangeHornSound : ActionSingleUseBase
{
    HRZ_Horn hornItem;

	void HRZ_ActionChangeHornSound ()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ITEM_ON;
	}

	override void CreateConditionComponents ()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
        string result = "Sound: ";
        if (hornItem)
        {
            string name = hornItem.GetCurrentHornSoundName();
            result = result + name;
        }
		return result;
	}

	override bool HasTarget () { return false; }

	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
        hornItem = NULL;
		if (item)
        {
            hornItem = HRZ_Horn.Cast(item);
            return true;
        }
		return false;
	}

	override void OnExecuteServer ( ActionData action_data )
	{
        if (hornItem) {
            hornItem.SelectNextHornSound();
        }
	}
};
