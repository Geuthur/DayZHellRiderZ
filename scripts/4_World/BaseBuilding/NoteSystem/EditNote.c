modded class WrittenNoteData
{	
    HRZ_PluginAdminLog 	m_NoteLog;
	protected string 	old_text;
	protected string 	new_text;
	protected int 		m_Color = 0;
	protected int 		penColor = 0;
	void WrittenNoteData(ItemBase parent)
    {
    }
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		ItemBase pen;
		ItemBase paper;
		auto param = new Param2<string, int>("", 0);
		
		//sent from server, executed on client
		if (rpc_type == ERPCs.RPC_WRITE_NOTE)
		{
			GetGame().GetMission().SetNoteMenu(GetGame().GetUIManager().EnterScriptedMenu(MENU_NOTE, GetGame().GetUIManager().GetMenu())); //NULL means no parent
			
			if (GetNoteInfo(pen,paper))
			{
				GetGame().GetMission().GetNoteMenu().InitNoteWrite(paper,pen,m_SimpleText);
			//PlayerBase bhplayer = GetPlayerByIdentity(sender);
			}
		}
		//sent from client (NoteMenu), executed on server
		if (rpc_type == ERPCs.RPC_WRITE_NOTE_CLIENT)
		{
			if (ctx.Read(param))
			{
				string old_string = m_SimpleText;
				old_text = m_SimpleText;
				SetNoteText(param.param1);
				SetNoteColor(param.param2);
				
				DepleteWritingImplement(m_WritingImplement,old_string,m_SimpleText);
				new_text = m_SimpleText;	
					if (GetNoteInfo(pen, paper))
                    {
                        HRZ_PaperToNoteLambda lambda = new HRZ_PaperToNoteLambda(paper, "HRZ_WrittenNote", this);
					
                        PlayerBase player = GetPlayerByIdentity(sender);
						m_NoteLog = HRZ_PluginAdminLog.Cast( GetPlugin(HRZ_PluginAdminLog) );
						m_NoteLog.HRZ_EditNote(player, old_text, new_text);
					
                        if (player.GetItemInHands() == paper)
                            player.ServerReplaceItemInHandsWithNew(lambda);
                        else
                            player.ServerReplaceItemWithNew(lambda);
                    }
			}
		}
		if (rpc_type == ERPCs.RPC_READ_NOTE)
		{
			if (ctx.Read(param))
			{
				SetNoteText(param.param1);
				SetNoteColor(param.param2);
				
				GetGame().GetMission().SetNoteMenu(GetGame().GetUIManager().EnterScriptedMenu(MENU_NOTE, GetGame().GetUIManager().GetMenu())); //NULL means no parent
			
				string m_Text = string.Format("%1^%2", m_Color, m_SimpleText); // hack to set text color
				
				GetGame().GetMission().GetNoteMenu().InitNoteRead(m_Text);
			
			}
		}
	}
	
    protected PlayerBase GetPlayerByIdentity(PlayerIdentity identity)
    {
        int highBits, lowBits;

        if (!GetGame().IsMultiplayer())
            return PlayerBase.Cast(GetGame().GetPlayer());

        if (identity == null)
            return null;

        GetGame().GetPlayerNetworkIDByIdentityID(identity.GetPlayerId(), lowBits, highBits);
        return PlayerBase.Cast(GetGame().GetObjectByNetworkId(lowBits, highBits));
    }
	
    int GetNoteColor()
	{
		return m_Color;
	}
	
	void SetNoteColor(int penColor)
	{
		m_Color = penColor;
	}
}