class HRZ_CraftFactionArmband extends RecipeBase
{	
    ref TStringArray FraktionArmbands = {
        "HRZ_Armband_Geuthur",
        "HRZ_Armband_Test"
	};

	override void Init()
	{
		m_Name = "Stelle Fraktion Armband Her";
		m_IsInstaRecipe = false;//should this recipe be performed instantly without animation
		m_AnimationLength = 1.5;//animation length in relative time units
		m_Specialty = 0.02;// value > 0 for roughness, value < 0 for precision
		
		
		//conditions
		m_MinDamageIngredient[0] = -1;//-1 = disable check
		m_MaxDamageIngredient[0] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[0] = 1;//-1 = disable check
		m_MaxQuantityIngredient[0] = -1;//-1 = disable check
		
		m_MinDamageIngredient[1] = -1;//-1 = disable check
		m_MaxDamageIngredient[1] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[1] = 50;//-1 = disable check
		m_MaxQuantityIngredient[1] = -1;//-1 = disable check
		//----------------------------------------------------------------------------------------------------------------------
		
		//INGREDIENTS
		//ingredient 1
		InsertIngredient(0,"Armband_White");//you can insert multiple ingredients this way
		
		m_IngredientAddHealth[0] = 0;// 0 = do nothing
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = -1;// 0 = do nothing
		m_IngredientDestroy[0] = false;//true = destroy, false = do nothing
		m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		
		//ingredient 2
		InsertIngredient(1,"SewingKit");
		
		m_IngredientAddHealth[1] = 0;// 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = -50;// 0 = do nothing
		m_IngredientDestroy[1] = false;// false = do nothing
		m_IngredientUseSoftSkills[1] = true;// set 'true' to allow modification of the values by softskills on this ingredient
		//----------------------------------------------------------------------------------------------------------------------
	}

    string GetFactionArmband(string faction)
    {
        if (faction == "")
        {
            return "";
        }
        faction = "HRZ_Armband_" + faction;
		for ( int i = 0; i < FraktionArmbands.Count(); ++i ) {
            if (faction == FraktionArmbands[i]) {
                return faction;
            }
        }
        return "";        
    }


	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
        HRZ_PermissionManager pm = GetHRZPermissionManager();
        string faction = pm.GetFaction(player);
		//Print(faction);
        if (GetFactionArmband(faction) != "")
        {
            return true;
        }
        return false;

	}

	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight)
	{
        HRZ_PermissionManager pm = GetHRZPermissionManager();
        string faction = pm.GetFaction(player);
        string result = GetFactionArmband(faction);
        if (result == "")
        {
            return;
        }        
        MiscGameplayFunctions.TurnItemIntoItemEx(player, new TurnItemIntoItemLambda(ingredients[0], result, player));
	}
};