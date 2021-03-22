modded class PluginLifespan extends PluginBase
{
    protected ref map<string, ref map<string, ref array<ref LifespanLevel>>> m_HRZ_FacepaintLevels;


    override void UpdateLifespan( PlayerBase player, bool force_update = false )
    {
        super.UpdateLifespan(player, force_update);

        HRZ_UpdateFacePaintLevel(player, force_update);
    }

    override void SynchBeardVisual( PlayerBase player, int state )
    {
        super.SynchBeardVisual(player, state);
        HRZ_UpdateFacePaintLevel(player, true);
    }

    void HRZ_UpdateFacePaintLevel( PlayerBase player, bool force_update = false )
    {
        if (!player.IsAlive())
            return;

        if (!m_HRZ_FacepaintLevels)
            return;

		int slot_id = InventorySlots.GetSlotIdFromString("Head");	
		EntityAI players_head = player.GetInventory().FindPlaceholderForSlot( slot_id );        
        string fpName = player.HRZ_GetFacePaint();
        int level = 0;
        LifespanLevel current_level;
        LifespanLevel prev_level;

		if ( m_PlayerCurrentLevel.Contains(player) )
		{
			current_level = m_PlayerCurrentLevel.Get( player );
            level = current_level.GetLevel();
        }

        if (!fpName || fpName == "None")
        {
            if (players_head)
            {
                if (current_level)
                {
                    if ( level == LifeSpanState.BEARD_EXTRA)
                    {
                        players_head.SetObjectTexture( 0, current_level.GetTextureName() );
                        players_head.SetObjectMaterial( 0, current_level.GetMaterialName() );                    
                        array< ref LifespanLevel> lifespan_levels = m_LifespanLevels.Get( player.GetPlayerClass() );
                        prev_level = lifespan_levels.Get(LifeSpanState.BEARD_LARGE);                    
                        player.SetFaceTexture(prev_level.GetTextureName());
                        player.SetFaceMaterial(prev_level.GetMaterialName());
                    } 
                    else 
                    {
                        players_head.SetObjectMaterial( 0, "");
                        players_head.SetObjectTexture( 0, "");
                        player.SetFaceTexture(current_level.GetTextureName());
                        player.SetFaceMaterial(current_level.GetMaterialName());
                    } 
                } else {
                    // woman
                    string player_class = player.GetPlayerClass();
                    players_head.SetObjectMaterial( 0, "");
                    players_head.SetObjectTexture( 0, "");
                    player.SetFaceMaterial(m_BloodyHands.Get(player_class).GetMaterial(BloodyHands.MATERIAL_TYPE_NORMAL));
                }
            }
            return;
        }

		if( players_head )
		{
            map <string, ref array<ref LifespanLevel>> fps = m_HRZ_FacepaintLevels.Get(player.GetPlayerClass());
            array <ref LifespanLevel> fpLevels = fps.Get(fpName);
            LifespanLevel fpLevel = fpLevels.Get(level);
            if ( level == LifeSpanState.BEARD_EXTRA)
            {
                prev_level = fpLevels.Get(LifeSpanState.BEARD_LARGE);
                players_head.SetObjectMaterial(0 , fpLevel.GetMaterialName());
                player.SetFaceMaterial(prev_level.GetMaterialName());
            } 
            else 
            {
                players_head.SetObjectMaterial( 0, "");
                player.SetFaceMaterial(fpLevel.GetMaterialName());
            }            
        }
    }


    override void LoadFromCfg()
    {
        super.LoadFromCfg();
        m_HRZ_FacepaintLevels = new map<string, ref map<string, ref array<ref LifespanLevel>>>;

		string config_name = "CfgVehicles";
		int config_count = GetGame().ConfigGetChildrenCount( config_name );
			
		int i, j, k, l, m;
		
		for ( i = 0; i < config_count; i++ )
		{
			string survivor_name = "";
			GetGame().ConfigGetChildName( config_name, i, survivor_name );
			
			if ( survivor_name != "" && survivor_name != "access" )
			{
				if ( GetGame().IsKindOf(survivor_name, "SurvivorMale_Base")  ||  GetGame().IsKindOf(survivor_name, "SurvivorFemale_Base") )
				{
					string survivor_path = config_name + " " + survivor_name;
					int survivor_lifespan_count = GetGame().ConfigGetChildrenCount( survivor_path );

					for ( j = 0; j < survivor_lifespan_count; j++ )
					{
						string survivor_lifespan_name = "";
						GetGame().ConfigGetChildName( survivor_path, j, survivor_lifespan_name );
						
						string survivor_lifespan_path = survivor_path + " " + survivor_lifespan_name;

						if ( survivor_lifespan_name == "Facepaint" )
						{
							int survivor_lifespan_facepaint_count = GetGame().ConfigGetChildrenCount( survivor_lifespan_path );

                            ref map<string, ref array<ref LifespanLevel>> facepaint_PaintLevels = new map<string, ref array< ref LifespanLevel>>;
							
							for ( k = 0; k < survivor_lifespan_facepaint_count; k++ )
							{
								string survivor_lifespan_facepaint_name = "";
								GetGame().ConfigGetChildName( survivor_lifespan_path, k, survivor_lifespan_facepaint_name );
								
								string survivor_lifespan_facepaint_path = survivor_lifespan_path + " " + survivor_lifespan_facepaint_name;

                                ref TStringArray materials = new TStringArray;
                                int cfg_class_member_member_variable_count = GetGame().ConfigGetChildrenCount( survivor_lifespan_facepaint_path );
                                
                                for ( l = 0; l < cfg_class_member_member_variable_count; l++ )
                                {
                                    string survivor_lifespan_facepaint_material_name = "";
                                    GetGame().ConfigGetChildName( survivor_lifespan_facepaint_path, l, survivor_lifespan_facepaint_material_name );
                                    string survivor_lifespan_facepaint_material_path = survivor_lifespan_facepaint_path + " " + survivor_lifespan_facepaint_material_name;
                                    
                                    if ( survivor_lifespan_facepaint_material_name == "mat" )
                                    {
                                        GetGame().ConfigGetTextArray( survivor_lifespan_facepaint_material_path, materials );
                                                                                
                                        ref array<ref LifespanLevel> facepaint_levels = new array< ref LifespanLevel>;
                                        int level_count = materials.Count();
                                        for (m = 0; m  < level_count; m++)
                                        {
                                            facepaint_levels.Insert(new LifespanLevel(m, 0.0, "", materials.Get(m)));
                                        }
                                        
                                        if ( facepaint_levels.Count() > 0 )
                                        {
                                            facepaint_PaintLevels.Set( survivor_lifespan_facepaint_name, facepaint_levels );
                                        }
                                    }
                                }
                            }
                            m_HRZ_FacepaintLevels.Set(survivor_name, facepaint_PaintLevels);
                        }
                    }
                }
            }
        }
    }

}