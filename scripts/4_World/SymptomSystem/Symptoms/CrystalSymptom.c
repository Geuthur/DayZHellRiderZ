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
  
  override void OnUpdateClient(PlayerBase player, float deltatime)
  {
  }
  
  override void OnGetActivatedServer(PlayerBase player)
  {
  }
  
  override void OnGetActivatedClient(PlayerBase player)
  {
        super.OnGetActivatedClient(player);

        Event_OnActivatedClient.Invoke(player, Type()); // pass player pointer and typename
	
		PPEffects.SetVignetteEffectValue(2, 3, 250, 127, 4, 0.2);
		PPEffects.SetBloodSaturation(5);
		
		HRZ_PPEffects.SetChromAbers(0.1, 0.1);
		HRZ_PPEffects.SetCrystalDynamic(20.0);
		HRZ_PPEffects.SetCrystalRotiBlur(0.50, 2.50, 10.0);
		HRZ_PPEffects.SetCrystalRadialBlur(0, 0, 0.76, 0);
  }
  
  override void OnGetDeactivatedServer(PlayerBase player)
  {
  Debug.Log("OnGetDeactivated ShakeSymptom called", "PlayerSymptom");
  }
  
  override void OnGetDeactivatedClient(PlayerBase player)
  {
        super.OnGetDeactivatedClient(player);

        Event_OnDeactivatedClient.Invoke(player, Type()); // pass player pointer and typename

		PPEffects.ResetVignettes();
		PPEffects.SetBloodSaturation(1);

		HRZ_PPEffects.ResetAll();
		
  Debug.Log("OnGetDeactivated ShakeSymptom called", "PlayerSymptom");
  }
 };