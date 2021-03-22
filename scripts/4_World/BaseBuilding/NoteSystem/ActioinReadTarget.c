class HRZ_ActionReadPaperTarget : ActionInteractBase
{
    override string GetText()
	{
		return "#read";
	}

	override bool IsInstant()
	{
		return true;
	}

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
		if (target && target.GetObject().IsInherited(HRZ_WrittenNote))
			return true;

        return false;
    }

	override void OnStartClient(ActionData action_data)
	{
		if (GetGame().GetUIManager() && GetGame().GetUIManager().IsMenuOpen(MENU_NOTE))
            GetGame().GetUIManager().FindMenu(MENU_NOTE).Close();
	}

    override void OnStartServer(ActionData action_data)
	{
        ItemBase paper_item = ItemBase.Cast(action_data.m_Target.GetObject());
		auto text = new Param2<string, int>(paper_item.GetWrittenNoteData().GetNoteText(), paper_item.GetWrittenNoteData().GetNoteColor());
        paper_item.RPCSingleParam(ERPCs.RPC_READ_NOTE, text, true, action_data.m_Player.GetIdentity());
	}
}