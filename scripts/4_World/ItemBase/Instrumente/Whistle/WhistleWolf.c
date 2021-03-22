enum HRZ_SoundTypeWhistleWolf
{
	DEFAULT		= 0;
    STOP = 1;
}

class HRZ_Whistle_Wolf : Inventory_Base
{	
    ref protected EffectSound 	m_WhistleSound;

	override void SetActions()
	{
		super.SetActions();		
		AddAction(HRZ_ActionBlowWhistleWolf);
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext  ctx) 
	{
		super.OnRPC(sender, rpc_type, ctx);
			
		switch(rpc_type)
		{
			case HRZ_SoundTypeWhistleWolf.DEFAULT:
				PlayWhistleSound();
                break;
            case HRZ_SoundTypeWhistleWolf.STOP:
                if (m_WhistleSound)
                {
                    m_WhistleSound.SoundStop();
                }
                break;
		}
	}

	void PlayWhistleSound()
	{
		m_WhistleSound = SEffectManager.PlaySoundOnObject( "HRZ_WhistleWolf_SoundSet", this );
		m_WhistleSound.SetSoundAutodestroy( true );
	}
};