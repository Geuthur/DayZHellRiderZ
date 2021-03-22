class HRZ_ActionChangeFacePaintStyle : ActionSingleUseBase
{

    HRZ_FacePaint_Base facepaintItem;

	void HRZ_ActionChangeFacePaintStyle ()
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
        string result = "Wahl: ";
        if (facepaintItem)
        {
            string name = facepaintItem.GetCurrentFacePaintName();
            result = result + name;
        }
		return result;
	}

	override bool HasTarget () { return false; }

	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
        facepaintItem = NULL;
		if (item)
        {
            facepaintItem = HRZ_FacePaint_Base.Cast(item);
            return true;
        }
		return false;
	}

	override void OnExecuteServer ( ActionData action_data )
	{
        if (facepaintItem) {
            facepaintItem.SelectNextFacePaint();
        }
	}
};
