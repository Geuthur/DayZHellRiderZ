class HRZ_TestSymptom extends SymptomBase
 {
	
	float m_BlurDuration;
	float m_BlurStrength;
	float m_EffectTime;
	float m_EffectStartTime;
	float m_Time;
	
	const float BLUR_STRENGTH_MIN = 0.1;
	const float BLUR_STRENGTH_MAX = 0.9;
	
	const int BLUR_DURATION_TIME_MIN = 1;
	const int BLUR_DURATION_TIME_MAX = 3;
	
	const int MIN_TIME_BETWEEN_EFFECTS = 1;
	const int MAX_TIME_BETWEEN_EFFECTS = 3;
	
	private const float 					PULSE_PERIOD = 0.1; //The time it takes for pulse to do a full cycle
	private const float 					PULSE_AMPLITUDE = 0.2; //This is a multiplier, keep below 1 or expect the unexpected
	private 	  float 					m_PulseTimer;
	
	private	float 							m_LerpRes; //Lerp result
	private	float m_HRZTest;
	private float m_cycle = 10;
	
  //this is just for the Symptom parameters set-up and is called even if the Symptom doesn't execute, don't put any gameplay code in here
  override void OnInit()
  {
	m_SymptomType = SymptomTypes.SECONDARY;
	m_Priority = 0;
	m_ID = HRZ_SymptomIDs.SYMPTOM_TEST;
	m_DestroyOnAnimFinish = true;
	m_IsPersistent = false;
	m_SyncToClient = true;
  }
  
  override void OnUpdateServer(PlayerBase player, float deltatime)
  {
  }
  
  override void OnUpdateClient(PlayerBase player, float deltatime)
  {		
		/*
		m_PulseTimer += deltatime;
		int m_cycle = m_PulseTimer;
		if (m_cycle > 5 && m_cycle < 11){
		Print ("Sym:" + m_PulseTimer);
		HRZ_PPEffects.CrazyPulsingRadialEffect(HRZ_EffectID.Crystal, 0.01);
		}*/ 
		//HRZ_PPEffects.DarkWorldEffect(HRZ_EffectID.Blur, 1);
		HRZ_PPEffects.WabbleEffect(HRZ_EffectID.Blur, 0.1); 
		/*
			int m_cycle = m_PulseTimer;
			if (m_cycle == 5){
			EffectSound sound =	SEffectManager.PlaySound( "HRZ_Drug1_SoundSet", GetCurrentPosition() );
			sound.SetSoundAutodestroy( true );
			}
		*/
  }

	private float LerpVignette(float x, float y, float deltatime)
	{
		float output;
		output = Math.Lerp(x, y, deltatime);
		return output;
	}
	
  override void OnGetActivatedServer(PlayerBase player)
  {
  }
  
  override void OnGetActivatedClient(PlayerBase player)
  {
        super.OnGetActivatedClient(player);

        Event_OnActivatedClient.Invoke(player, Type()); // pass player pointer and typename
		
		//HRZ_PPEffects.SetChromAbersEffectValue(HRZ_EffectID.Blur,0, 0);

		//HRZ_PPEffects.HRZ_SetVignetteEffectValue(HRZ_EffectID.Blur, 3, 250, 127, 4, 0.2);
		PPEffects.SetBloodSaturation(1);
		
		//HRZ_PPEffects.SetDynamicEffectValue(HRZ_EffectID.Blur,20.0);
		
		//HRZ_PPEffects.SetRotiBlurEffectValue(HRZ_EffectID.Blur,0.50, 2.50, 10.0);
		//HRZ_PPEffects.SetRadialBlurEffectValue(HRZ_EffectID.Blur,0, 0, 0.76, 0);
  }
  
  override void OnGetDeactivatedServer(PlayerBase player)
  {
  Debug.Log("OnGetDeactivated ShakeSymptom called", "PlayerSymptom");
  }
  
  override void OnGetDeactivatedClient(PlayerBase player)
  {
        super.OnGetDeactivatedClient(player);

        Event_OnDeactivatedClient.Invoke(player, Type()); // pass player pointer and typename
		
		HRZ_PPEffects.ResetAll();
		PPEffects.ResetAll();
		
  Debug.Log("OnGetDeactivated ShakeSymptom called", "PlayerSymptom");
  }
 };