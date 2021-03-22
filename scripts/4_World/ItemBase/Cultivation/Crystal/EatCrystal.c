class HRZ_ActionEatCrackCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(5);
	}
};

class HRZ_ActionEatCrack: ActionContinuousBase
{
	void HRZ_ActionEatCrack()
	{
		m_CallbackClass = HRZ_ActionEatCrackCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_EAT;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_FullBody = false;
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTSelf;
	}
	
	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsMultiplayer() && GetGame().IsServer())
		{
            return true;
        }
		return true;
	}
	
	override bool HasProneException()
	{
		return true;
	}
	
	override bool HasTarget()
	{
		return false;
	}
	
	override string GetText()
	{
		return "Iss Crystal Meth";
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
        HRZ_Crystal_Base ps = HRZ_Crystal_Base.Cast(action_data.m_MainItem);

        if ( ps )
        {
		    action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
            ps.AddQuantity(-25);
            if (ps.GetQuantity() <= 0 ) {
               ps.Delete();
            }
        }
		EntityAI item = action_data.m_MainItem;
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		{
			if(action_data.m_MainItem && player)
			{
				player.GetModifiersManager().ActivateModifier(102);
			}
		}
	}

	override void OnFinishProgressClient(ActionData action_data)
	{
		if( GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(isHigh, 1000, false, action_data.m_Player);
				
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(notHigh, 190000, false, action_data.m_Player);
		}
	}

	void isHigh(ActionData action_data, PlayerBase player)
	{
		Print( "[HRZ] Crack gegessen" );
		//registers
		if( GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
		Material matiColors = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/glow");
		Material dynamic = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/dynamicblur");
		Material radiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/radialblur");
		Material rotiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/rotblur");
		Material chromAbers = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/chromaber");

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
	}

	void notHigh(ActionData action_data, PlayerBase player)
	{
		if( GetGame().IsClient() || !GetGame().IsMultiplayer() )
		{
		//registers
		Material matiColors = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/glow");
		Material dynamic = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/dynamicblur");
		Material radiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/radialblur");
		Material rotiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/rotblur");
		Material chromAbers = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/chromaber");
		//settings

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
		}
	}
};
