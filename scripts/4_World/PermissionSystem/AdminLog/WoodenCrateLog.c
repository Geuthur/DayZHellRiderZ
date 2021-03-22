modded class DeCraftWoodenCrate extends RecipeBase
{
    HRZ_PluginAdminLog m_WoodCrateDeLog;

	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
        super.Do(ingredients, player, results, specialty_weight);

        m_WoodCrateDeLog = HRZ_PluginAdminLog.Cast( GetPlugin(HRZ_PluginAdminLog) );
        m_WoodCrateDeLog.HRZ_DecraftWoodenCrate(player);
    }   
}


