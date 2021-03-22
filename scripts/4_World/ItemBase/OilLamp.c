class HRZ_Oillamp extends ItemBase
{
	TorchLight	m_Light;
	Particle 				m_FireParticle;
	vector 					m_ParticleLocalPos = Vector(0, 0.02, 0);

	private const string GAS_LIGHT_MATERIAL_ON 		= "dz\\gear\\cooking\\data\\GasLightOn.rvmat";
	private const string GAS_LIGHT_MATERIAL_OFF 	= "dz\\data\\data\\default.rvmat";

	//sound
	const string SOUND_BURNING 		= "portablegaslamp_burn_SoundSet";
	const string SOUND_TURN_ON		= "portablegaslamp_turn_on_SoundSet";
	const string SOUND_TURN_OFF		= "portablegaslamp_turn_off_SoundSet";
	
	protected EffectSound m_SoundBurningLoop;
	protected EffectSound m_SoundTurnOn;
	protected EffectSound m_SoundTurnOff;


	//--- POWER EVENTS
	override void OnSwitchOn()
	{
		super.OnSwitchOn();
		m_Light.m_TorchRadius = 20;
		//sound (client only)
		SoundTurnOn();
	}

	override void OnSwitchOff()
	{
		super.OnSwitchOff();
		
		//sound (client only)
		SoundTurnOff();
	}
	
	override void OnWorkStart()
	{
		if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() ) // client side
		{
			m_Light = TorchLight.Cast( ScriptedLightBase.CreateLight( TorchLight, "0 0 0") );
			m_Light.AttachOnMemoryPoint(this, "light_oillamp");
			m_Light.m_TorchRadius = 20;
			if (!m_FireParticle)
			m_FireParticle = Particle.PlayOnObject(ParticleList.ZIPPOFLAME, this, m_ParticleLocalPos + "0 -0.30 0", Vector(0,0,0), true);
			m_FireParticle.SetWiggle(3,0.1);

				m_FireParticle.ScaleParticleParamFromOriginal(EmitorParam.SIZE, 1.5);
		}
		
	
		//sound (client only)
		SoundBurningStart();
	}

	override void OnWorkStop()
	{
		if (m_Light)
			m_Light.FadeOut();
		
		
		//sound (client only)
		SoundBurningStop();
		StopAllParticles();
	}
	void StopAllParticles()
	{
		if (m_FireParticle)
		{
			m_FireParticle.Stop();
		}
	}
	
	//================================================================
	// SOUNDS
	//================================================================
	protected void SoundBurningStart()
	{
		PlaySoundSetLoop( m_SoundBurningLoop, SOUND_BURNING, 0.1, 0.3 );
	}
	
	protected void SoundBurningStop()
	{
		StopSoundSet( m_SoundBurningLoop );
	}	

	protected void SoundTurnOn()
	{
		PlaySoundSet( m_SoundTurnOn, SOUND_TURN_ON, 0.1, 0.1 );
	}
	
	protected void SoundTurnOff()
	{
		PlaySoundSet( m_SoundTurnOff, SOUND_TURN_OFF, 0.1, 0.1 );
	}

	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
		AddAction(ActionTurnOnWhileOnGround);
		AddAction(ActionTurnOffWhileOnGround);
	}	
}