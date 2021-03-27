class HRZ_KokainSymptom extends SymptomBase
 {
	
	float m_BlurDuration;
	float m_BlurStrength;
	float m_EffectTime;
	float m_EffectStartTime;
	float m_Time;
	
	const float BLUR_STRENGTH_MIN = 0.1;
	const float BLUR_STRENGTH_MAX = 0.9;
	
	const int BLUR_DURATION_TIME_MIN = 3;
	const int BLUR_DURATION_TIME_MAX = 30;
	
	const int MIN_TIME_BETWEEN_EFFECTS = 12.0;
	const int MAX_TIME_BETWEEN_EFFECTS = 30.0;
	
  //this is just for the Symptom parameters set-up and is called even if the Symptom doesn't execute, don't put any gameplay code in here
  override void OnInit()
  {
	m_SymptomType = SymptomTypes.SECONDARY;
	m_Priority = 0;
	m_ID = HRZ_SymptomIDs.SYMPTOM_KOKAIN;
	m_DestroyOnAnimFinish = true;
	m_IsPersistent = false;
	m_SyncToClient = true;
  }
  
  override void OnUpdateServer(PlayerBase player, float deltatime)
  {
  }
  
  override void OnUpdateClient(PlayerBase player, float deltatime)
  {		
		
		HRZ_PPEffects.SetDynamicEffectValue(HRZ_EffectID.Kokain, 10.0);
		
		HRZ_PPEffects.SetRotiBlurEffectValue(HRZ_EffectID.Kokain, 0, 1.0, 2.0);
		
		HRZ_PPEffects.SetRadialBlurEffectValue(HRZ_EffectID.Kokain, 0, 0, 0.76, 0);
		
		m_Time += deltatime;
		if( m_EffectStartTime <= 0 )
		{
			m_EffectStartTime = Math.RandomFloatInclusive(MIN_TIME_BETWEEN_EFFECTS, MAX_TIME_BETWEEN_EFFECTS);
			m_BlurDuration = Math.RandomFloatInclusive(BLUR_DURATION_TIME_MIN, BLUR_DURATION_TIME_MAX);
			m_BlurStrength = Math.RandomFloat(BLUR_STRENGTH_MIN, BLUR_STRENGTH_MAX);
		}
		
		if( m_EffectStartTime > 0 && m_Time > m_EffectStartTime )
		{
			m_EffectTime += deltatime / m_BlurDuration;
			
			float cos_value = Math.Sin(m_EffectTime  * Math.PI);
			float kokain = cos_value * m_BlurStrength;

			HRZ_PPEffects.SetRotiBlurEffectValue(HRZ_EffectID.Kokain, kokain, 1.0, 2.0);
			
			GetGame().GetPlayer().GetCurrentCamera().SpawnCameraShake(kokain,5,4,2);
			
			if( m_EffectTime >= 1 )
			{
				m_EffectTime = 0;
				m_EffectStartTime = -1;
				m_Time = 0;
			}
		}
  }
  
  override void OnGetActivatedServer(PlayerBase player)
  {
  }
  
  override void OnGetActivatedClient(PlayerBase player)
  {
        super.OnGetActivatedClient(player);

        Event_OnActivatedClient.Invoke(player, Type()); // pass player pointer and typename
  }
  
  override void OnGetDeactivatedServer(PlayerBase player)
  {
  Debug.Log("OnGetDeactivated ShakeSymptom called", "PlayerSymptom");
  }
  
  override void OnGetDeactivatedClient(PlayerBase player)
  {
        super.OnGetDeactivatedClient(player);

        Event_OnDeactivatedClient.Invoke(player, Type()); // pass player pointer and typename
		
		HRZ_PPEffects.ResetAllEffects(HRZ_EffectID.Kokain);
		
  Debug.Log("OnGetDeactivated ShakeSymptom called", "PlayerSymptom");
  }
 };