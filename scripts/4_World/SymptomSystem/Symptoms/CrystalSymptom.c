class HRZ_CrystalSymptom extends SymptomBase
 {
	//this is just for the Symptom parameters set-up and is called even if the Symptom doesn't execute, don't put any gameplay code in here
  override void OnInit()
  {
	m_SymptomType = SymptomTypes.SECONDARY;
	m_Priority = 0;
	m_ID = HRZ_SymptomIDs.SYMPTOM_CRYSTAL;
	m_DestroyOnAnimFinish = true;
	m_IsPersistent = false;
	m_SyncToClient = true;
  }
  
  override void OnUpdateServer(PlayerBase player, float deltatime)
  {
  }
  
  private 	  float 					m_PulseTimer;
  override void OnUpdateClient(PlayerBase player, float deltatime)
  {
		m_PulseTimer += deltatime;
		int m_cycle = m_PulseTimer;
		if (m_cycle > 5 && m_cycle < 11){
		HRZ_PPEffects.PulsingRadialEffect(HRZ_EffectID.Crystal, 1);
		} else {
		HRZ_PPEffects.SetRadialBlurEffectValue(HRZ_EffectID.Crystal,0, 0, 0.76, 0);
		}
  }
  
  override void OnGetActivatedServer(PlayerBase player)
  {
  }
	
  override void OnGetActivatedClient(PlayerBase player)
  {
        super.OnGetActivatedClient(player);

        Event_OnActivatedClient.Invoke(player, Type()); // pass player pointer and typename
		
		HRZ_PPEffects.SetChromAbersEffectValue(HRZ_EffectID.Crystal,0.1, 0.1);
		HRZ_PPEffects.HRZ_SetVignetteEffectValue(HRZ_EffectID.Crystal, 3, 250, 127, 4, 0.2);
		PPEffects.SetBloodSaturation(5);
		HRZ_PPEffects.SetDynamicEffectValue(HRZ_EffectID.Crystal,20.0);
		HRZ_PPEffects.SetRotiBlurEffectValue(HRZ_EffectID.Crystal,0.50, 2.50, 10.0);
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