modded class NoteMenu
{
    //string cfgPath = "CfgVehicles " + m_Pen.GetType() + " CfgColor" ;
	protected int m_Color;
	
    override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("Client/gui/NoteMenu.layout");
		m_edit = MultilineEditBoxWidget.Cast( layoutRoot.FindAnyWidget("EditWidget") );
		//m_html = HtmlWidget.Cast( layoutRoot.FindAnyWidget("HtmlWidget") );
		m_confirm_button = ButtonWidget.Cast( layoutRoot.FindAnyWidgetById(IDC_OK) );

		return layoutRoot;
	}
	
	override void InitNoteRead(string text = "")
	{
		m_IsWriting = false;
		
		if (m_edit)
		{
			m_edit.Enable(false);
			
			m_Color = text.Substring(0, text.IndexOf("^")).ToInt();
			string textNew = text.SubstringInverted(text, 0, text.IndexOf("^") + 1);
			//string textNew = text;
			
			if (m_Color == 0)
			m_Color = 0xFF000000;
			
			m_edit.SetText(textNew);
			m_edit.SetColor(m_Color);

		}

		m_confirm_button.Show(false);
	}

	override void InitNoteWrite(EntityAI paper, EntityAI pen, string text = "")
	{
		m_IsWriting = true;
		
		if (m_edit)
		{
			m_edit.Enable(true);

			m_Paper = ItemBase.Cast(paper);
			m_Pen = pen;
			m_PenColor = m_Pen.ConfigGetString("writingColor");
			switch (m_PenColor) {
			case "#000000": { m_Color = 0xFF000000;} break;// Black
			case "#B40404" : { m_Color = 0xFFB40404;} break;// Green
			case "#088A08" : { m_Color = 0xFF088A08;} break;// Red
			case "#0431B4" : { m_Color = 0xFF0431B4;} break;// Blue
			case "#FF69B4" : { m_Color = 0xFFFFC0CB;} break;// Pink
			case "#FF8100" : { m_Color = 0xFFFF8100;} break;// Orange
			case "#00F9FF" : { m_Color = 0xFF00F9FF;} break;// Turkis
			}

			//protected ItemBase m_HRZ;
			//string cfgPath = "CfgVehicles " + m_HRZ.GetType() + " CfgColor" ;
			// hrzcolor = GetGame().ConfigGetTextOut( cfgPath + " color" );
			if (m_Color == 0)
				m_Color = 0xFF000000;
			
			m_edit.Show(true);
			m_edit.SetText(text);
			m_edit.SetColor(m_Color);
		}
		m_confirm_button.Show(true);
	}
	

	override bool OnClick(Widget w, int x, int y, int button)
	{
		super.OnClick(w, x, y, button);
		
		switch (w.GetUserID())
		{
			case IDC_CANCEL:
				Close();
				return true;
			case IDC_OK:
				if (m_Paper && m_Pen && m_IsWriting)
				{
					string edit_text;
					m_edit.GetText(edit_text);
					edit_text = MiscGameplayFunctions.SanitizeString(edit_text);
					auto text = new Param2<string, int>(edit_text, m_Color);
					m_Paper.RPCSingleParam(ERPCs.RPC_WRITE_NOTE_CLIENT, text, true);
				}
				Close();
			return true;
		}

		return false;
	}
}