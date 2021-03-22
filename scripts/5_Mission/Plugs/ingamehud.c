modded class IngameHud extends Hud
{
    private Widget m_HRZ_IconsRootWidget;
    private ImageWidget m_HRZ_MuteIcon;
    private ImageWidget m_HRZ_DrugIcon;
	
    private bool m_HRZ_IsMuteVisible = false;
    private bool m_HRZ_IsDrugVisible = false;
	
	void IngameHud()
	{
		if(GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
            m_HRZ_IconsRootWidget = GetGame().GetWorkspace().CreateWidgets("DayZHellRiderZ/scripts/layouts/hrz_hud.layout");

            if (m_HRZ_IconsRootWidget)
            {
                m_HRZ_MuteIcon = ImageWidget.Cast( m_HRZ_IconsRootWidget.FindAnyWidget("HRZMuteIcon"));
                m_HRZ_MuteIcon.Show(false);
				
                m_HRZ_DrugIcon = ImageWidget.Cast( m_HRZ_IconsRootWidget.FindAnyWidget("HRZDrugIcon"));
                m_HRZ_DrugIcon.Show(false);

                m_HRZ_IconsRootWidget.Show(true);               
            }
		}
	}

    void HRZ_UpdateIconsState()
    {              
        if (m_HRZ_IconsRootWidget)
        {
			if(HRZ_IsHudVisible() && GetHudState() && m_HRZ_IsMuteVisible)
			{
				m_HRZ_MuteIcon.Show(true);
			}
			else if(!HRZ_IsHudVisible() || !GetHudState() || !m_HRZ_IsMuteVisible)
			{
                m_HRZ_MuteIcon.Show(false);
			}
			if(HRZ_IsHudVisible() && GetHudState() && m_HRZ_IsDrugVisible)
			{
				m_HRZ_DrugIcon.Show(true);
			}
			else if(!HRZ_IsHudVisible() || !GetHudState() || !m_HRZ_IsDrugVisible)
			{
                m_HRZ_DrugIcon.Show(false);
			}
        }
    }

	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		PlayerBase player = GetGame().GetPlayer();
		
		if (!player)
        {
            return;
        }
		
		if (!player.IsAlive())
		{
            m_HRZ_IsMuteVisible = false;
            
		}
        HRZ_UpdateIconsState();
	}

	bool HRZ_IsMuteVisible()
	{
		return m_HRZ_IsMuteVisible;
	}

	void HRZ_SetMuteIcon(bool state)
	{
        m_HRZ_IsMuteVisible = state;
        HRZ_UpdateIconsState();
	} 
	
	void HRZ_SetDrugIcon(bool state)
	{
        m_HRZ_IsDrugVisible = state;
        HRZ_UpdateIconsState();
	} 

	bool HRZ_IsHudVisible()
	{
        if(m_HudHideUI || !m_HudState)
        {
            return false;
        }
        return true;
	}
	
	
}