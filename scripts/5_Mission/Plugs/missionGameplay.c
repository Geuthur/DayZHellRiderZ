modded class MissionGameplay extends MissionBase {

    private bool HRZ_Muted = false;
    private bool HRZ_AlwaysMute = false;

    private float HRZ_FadeTime = 0.5;
    private float HRZ_MuteFactor = 0.25;

    private UAInput HRZ_AutoMute;
    

    void OnSymptomActivate(PlayerBase player, typename symptomType)
    {
		IngameHud hud = IngameHud.Cast(GetHud());
		hud.HRZ_SetDrugIcon(true);         
        Print("Symptom activated: " + symptomType.ToString());
    }
	
    void OnSymptomDeactivate(PlayerBase player, typename symptomType)
    {
		IngameHud hud = IngameHud.Cast(GetHud());
		hud.HRZ_SetDrugIcon(false);         
        Print("Symptom deactivated: " + symptomType.ToString());
    }
	
	void MissionGameplay()
	{	
		// SymptomBase
        SymptomBase.Event_OnActivatedClient.Insert(OnSymptomActivate); // register our method to recieve events
        SymptomBase.Event_OnDeactivatedClient.Insert(OnSymptomDeactivate); // register our method to recieve events
		// Mute Toggle
        HRZ_AutoMute = GetUApi().GetInputByName("UAHRZToggleMute");
    }

	void ~MissionGameplay()
	{
		// SymptomBase
        SymptomBase.Event_OnActivatedClient.Remove(OnSymptomActivate); // unregister our method when mission is over
        SymptomBase.Event_OnDeactivatedClient.Remove(OnSymptomDeactivate); // unregister our method to recieve events
	}    
	
    override void OnUpdate( float timeslice )
	{
		super.OnUpdate( timeslice );
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if(!player)
        {
            return;
        }

        IngameHud hud = IngameHud.Cast(GetHud());

		if( player.IsAlive() && HRZ_AutoMute.LocalClick() && !IsControlDisabled() && !IsPaused() && GetGame().GetUIManager().GetMenu() == null)
		{
			HRZ_AlwaysMute = !HRZ_AlwaysMute;

            if (HRZ_AlwaysMute)
            {
                GetGame().GetSoundScene().SetSoundVolume(HRZ_MuteFactor*g_Game.m_volume_sound,HRZ_FadeTime);            
                hud.HRZ_SetMuteIcon(true);  
            }
            else
            {
                GetGame().GetSoundScene().SetSoundVolume(g_Game.m_volume_sound,HRZ_FadeTime);            
                hud.HRZ_SetMuteIcon(false);               
            }
		}

        if (player.GetCommand_Vehicle() && !HRZ_Muted)
        {
            HRZ_Muted = true;
            HRZ_AlwaysMute = true;
            GetGame().GetSoundScene().SetSoundVolume(HRZ_MuteFactor*g_Game.m_volume_sound,HRZ_FadeTime);            
            hud.HRZ_SetMuteIcon(true);
        } 
        else if (!player.GetCommand_Vehicle() && HRZ_Muted)
        {
            HRZ_Muted = false;
            HRZ_AlwaysMute = false;
            GetGame().GetSoundScene().SetSoundVolume(g_Game.m_volume_sound,HRZ_FadeTime);
            hud.HRZ_SetMuteIcon(false);
        }
		
		}
}