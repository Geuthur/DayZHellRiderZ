modded class PluginRecipesManager 
{
	override void RegisterRecipies()
    {
        super.RegisterRecipies();
		
		//Drugs System
		RegisterRecipe(new HRZ_CraftCigsCannabis);
		RegisterRecipe(new HRZ_CraftCigsCannabisTop);
        	RegisterRecipe(new HRZ_CraftCigsTabak);
        	RegisterRecipe(new HRZ_CraftPapers);
        	RegisterRecipe(new HRZ_CraftSherlockPipe);
		RegisterRecipe(new HRZ_CraftKokain);
		RegisterRecipe(new HRZ_CraftKokainPack);
		RegisterRecipe(new HRZ_CraftKokainSyringe);

		//Clothing System
		RegisterRecipe(new HRZ_craftBearcowl);
        	RegisterRecipe(new HRZ_craftWolfcowl);
		
		// PermissionSystem
		RegisterRecipe(new HRZ_CraftFactionArmband);	
		
		// NoteSystem
		//RegisterRecipe(new HRZ_WriteLetter);	Can't be get Worked atm

		//Instrument Base
		RegisterRecipe(new HRZ_CraftWhistle);

		//Medical Stuff
		RegisterRecipe(new HRZ_CombinePainkiller);
		RegisterRecipe(new HRZ_CombineVitatmin);
		RegisterRecipe(new HRZ_CombineCharCoal);
		RegisterRecipe(new HRZ_CombineChlor);
		RegisterRecipe(new HRZ_CombineTetra);

		//Tools
		RegisterRecipe(new HRZ_CombineMatchbox);
		RegisterRecipe(new HRZ_CraftWetzstone);

		// Ressources
		RegisterRecipe(new HRZ_CraftStoneChisel);
		RegisterRecipe(new HRZ_SawWoodenLog);
    }
}