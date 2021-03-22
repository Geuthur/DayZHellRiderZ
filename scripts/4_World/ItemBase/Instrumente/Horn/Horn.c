enum HRZ_SoundTypeHorn
{
	DRILL = 0;
    FIRSTCALL,
	RETREAT,
	RECALL,
    REVEILLE,
    TAPS,
    TOARMS,
	GUARD,
	ASSEMBLY,
	
}

class HRZ_Horn: Inventory_Base
{	
    ref protected EffectSound 	m_HornSound;
    protected int m_HornSoundIndex = 0;
    protected int m_MaxHornSoundIndex = 8;

    void HRZ_Horn()
    {
        RegisterNetSyncVariableInt("m_HornSoundIndex");
    }
    
	string GetCurrentHornSoundName()
	{
        switch (m_HornSoundIndex)
        {
			case HRZ_SoundTypeHorn.DRILL:
				return "Drill";
			case HRZ_SoundTypeHorn.FIRSTCALL:
				return "First Call";            
			case HRZ_SoundTypeHorn.RETREAT:
				return "Retreat";
			case HRZ_SoundTypeHorn.RECALL:
				return "Recall";
			case HRZ_SoundTypeHorn.REVEILLE:
				return "Reveille";
			case HRZ_SoundTypeHorn.TAPS:
				return "Taps";
			case HRZ_SoundTypeHorn.TOARMS:
				return "To Arms";
			case HRZ_SoundTypeHorn.GUARD:
				return "Guard";            
			case HRZ_SoundTypeHorn.ASSEMBLY:
				return "Assembly";
			break;
        }
        return "Retreat";
	}

    int GetHornSoundLength()
    {
        switch (m_HornSoundIndex)
        {
			case HRZ_SoundTypeHorn.DRILL:
				return 8;    
			case HRZ_SoundTypeHorn.FIRSTCALL:
				return 7;            
			case HRZ_SoundTypeHorn.RETREAT:
				return 27;
			case HRZ_SoundTypeHorn.RECALL:
				return 7;
			case HRZ_SoundTypeHorn.REVEILLE:
				return 23;
			case HRZ_SoundTypeHorn.TAPS:
				return 58;
			case HRZ_SoundTypeHorn.TOARMS:
				return 25;
			case HRZ_SoundTypeHorn.GUARD:
				return 12;
			case HRZ_SoundTypeHorn.ASSEMBLY:
				return 12;
			break;
        }
        return 27; // some default
    }

	void SelectNextHornSound()
	{
		m_HornSoundIndex++;
		if (m_HornSoundIndex > m_MaxHornSoundIndex)
			m_HornSoundIndex = 0;
        SetSynchDirty();            
	}    

	override void SetActions()
	{
		super.SetActions();
        AddAction(HRZ_ActionChangeHornSound);
		AddAction(HRZ_ActionBlowHorn);
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext  ctx) 
	{
		super.OnRPC(sender, rpc_type, ctx);

        if ( rpc_type == 0)
        {           
            switch(m_HornSoundIndex)
            {
                case HRZ_SoundTypeHorn.DRILL:
                    PlayHornSound("HRZ_Horn_SoundSet_Drill");
                    break;
                case HRZ_SoundTypeHorn.FIRSTCALL:
                    PlayHornSound("HRZ_Horn_SoundSet_FirstCall");
                    break;                
                case HRZ_SoundTypeHorn.RETREAT:
                    PlayHornSound("HRZ_Horn_SoundSet_Retreat");
                    break;
                case HRZ_SoundTypeHorn.RECALL:
                    PlayHornSound("HRZ_Horn_SoundSet_Recall");
                    break;
                case HRZ_SoundTypeHorn.REVEILLE:
                    PlayHornSound("HRZ_Horn_SoundSet_Reveille");
                    break;
                case HRZ_SoundTypeHorn.TAPS:
                    PlayHornSound("HRZ_Horn_SoundSet_Taps");
                    break;
                case HRZ_SoundTypeHorn.TOARMS:
                    PlayHornSound("HRZ_Horn_SoundSet_ToArms");
                    break;
                case HRZ_SoundTypeHorn.GUARD:
                    PlayHornSound("HRZ_Horn_SoundSet_Guard");
                    break;
                case HRZ_SoundTypeHorn.ASSEMBLY:
                    PlayHornSound("HRZ_Horn_SoundSet_Assembly");
                    break;
            }
        } 
        else
        {
            if (m_HornSound)
            {
                m_HornSound.SoundStop();
            }
        }
	}

	void PlayHornSound(string soundSet)
	{
		m_HornSound = SEffectManager.PlaySoundOnObject( soundSet, this );
		m_HornSound.SetSoundAutodestroy( true );
	}
};