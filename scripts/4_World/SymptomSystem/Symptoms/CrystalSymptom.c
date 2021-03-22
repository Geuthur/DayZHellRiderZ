class HRZ_CrystalSymptom extends SymptomBase
 {
	Material matiColors = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/glow");
	Material dynamic = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/dynamicblur");
	Material radiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/radialblur");
	Material rotiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/rotblur");
	Material chromAbers = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/chromaber");
	//settings
	
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
		
		chromAbers.SetParam( "PowerX", 0.1 );
		chromAbers.SetParam( "PowerY", 0.1 );

		matiColors.SetParam("Saturation", 5.0 );
		matiColors.SetParam("Vignette", 3.00);
		matiColors.SetParam("VignetteColor", 0.80);

		dynamic.SetParam("Blurriness", 20.0);

		rotiBlur.SetParam("Power", 0.50 );
		rotiBlur.SetParam("MinDepth", 2.50 );
		rotiBlur.SetParam("MaxDepth", 10.0 );

		radiBlur.SetParam("OffsetX", 0.76 );
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