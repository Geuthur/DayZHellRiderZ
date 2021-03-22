class HRZ_KokainSymptom extends SymptomBase
 {
	float m_BlurDuration;
	float m_BlurStrength;
	float m_EffectTime;
	float m_EffectStartTime;
	float m_Time;
	
	Material matiColors = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/glow");
	Material dynamic = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/dynamicblur");
	Material radiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/radialblur");
	Material rotiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/rotblur");
	Material chromAbers = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/chromaber");
	
	
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
		dynamic.SetParam("Blurriness", 10.0);

		rotiBlur.SetParam("MinDepth", 1.0 );
		rotiBlur.SetParam("MaxDepth", 2.0 );

		radiBlur.SetParam("OffsetX", 0.76 );
		
		//chromAbers.SetParam( "PowerX", 0.1 );
		//chromAbers.SetParam( "PowerY", 0.1 );

		//matiColors.SetParam("Saturation", 1.0 );
		//matiColors.SetParam("Vignette", 1.00);
		//matiColors.SetParam("VignetteColor", 0.40);
		
		m_Time += deltatime;
		if( m_EffectStartTime <= 0 )
		{
			m_EffectStartTime = Math.RandomFloatInclusive(MIN_TIME_BETWEEN_EFFECTS, MAX_TIME_BETWEEN_EFFECTS);
			m_BlurDuration = Math.RandomFloatInclusive(BLUR_DURATION_TIME_MIN, BLUR_DURATION_TIME_MAX);
			m_BlurStrength = Math.RandomFloat(BLUR_STRENGTH_MIN, BLUR_STRENGTH_MAX);
			//PrintString("m_BlurDuration=" +m_BlurDuration.ToString());
		}
		
		if( m_EffectStartTime > 0 && m_Time > m_EffectStartTime )
		{
			m_EffectTime += deltatime / m_BlurDuration;
			//m_EffectTime += deltatime;
			float cos_value = Math.Sin(m_EffectTime  * Math.PI);
			float kokain = cos_value * m_BlurStrength;
			//Print(kokain);
			rotiBlur.SetParam("Power", kokain + 0.5 );
			
			//PPEffects.SetTunnelVignette(kokain);
			//PrintString("cos=" +cos_value.ToString());
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

		chromAbers.SetParam( "PowerX", 0.0 );
		chromAbers.SetParam( "PowerY", 0.0 );

		matiColors.SetParam("Saturation", 1.0 );
		matiColors.SetParam("Vignette", 0.00);
		matiColors.SetParam("VignetteColor", 0.0);
		matiColors.SetParam("OverlayColor", 0 );
		
		dynamic.SetParam("Blurriness", 0.0);

		rotiBlur.SetParam("Power", 0.00 );
		rotiBlur.SetParam("MinDepth", 0.00 );
		rotiBlur.SetParam("MaxDepth", 0.00);

		radiBlur.SetParam("OffsetX", 0.00 );
  Debug.Log("OnGetDeactivated ShakeSymptom called", "PlayerSymptom");
  }
 };