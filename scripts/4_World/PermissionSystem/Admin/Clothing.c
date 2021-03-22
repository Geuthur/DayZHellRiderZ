//ItemBase backpack;
//if (backpack.GetAttachmentByType(Megaphone)) {
//    Print("Backpack has megaphone");
//}
// Delete Shirt from player
//GetGame().ObjectDelete(player.FindAttachmentBySlotName("Body"));
// Create new Shirt on player
//player.GetInventory().CreateAttachment("Shirt_RedCheck");
//player.FindAttachmentBySlotName( "Back" );
//GetAttachmentByConfigTypeName
//if (parent.FindAttachmentBySlotName("Body").IsKindOf("HRZ_Admin_Team"))
class HRZ_Admin_Team extends Clothing
{
	/*
    override void EEInit(){
		super.EEInit();
		SetObjectTexture(0, "Client\\clothes\\top\\admin\\HRZ_Admin.paa");
		SetObjectMaterial(0, "Client\\clothes\\top\\admin\\admin.rvmat");
		SetObjectTexture(1, "Client\\clothes\\top\\admin\\HRZ_Admin.paa");
		SetObjectMaterial(1, "Client\\clothes\\top\\admin\\admin.rvmat");
		SetObjectTexture(2, "Client\\clothes\\top\\admin\\HRZ_Admin.paa");
		SetObjectMaterial(2, "Client\\clothes\\top\\admin\\admin.rvmat");
	}
	*/
	
	/*
	protected bool m_IsAdminInActive = true;
	string role;
	override void OnWasAttached( EntityAI parent, int slot_id )
	{
	m_IsAdminInActive = false;
	}
	override bool CanPutInCargo ( EntityAI parent ){
				HRZ_PermissionManager pm = GetHRZPermissionManager();
				role = pm.GetRole(parent);
				if (role == "ADMIN")
				{
						//m_IsAdminInActive = false;
						return true;
				}
		return false;
	}

	override bool CanPutAsAttachment( EntityAI parent )
	{
		if(!super.CanPutAsAttachment(parent)) {return false;}
				//PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        return false;
	}
	
	override bool CanDetachAttachment( EntityAI parent )
	{
		return true;
		//return m_IsAdminInActive;
	}
	*/
	
	override void EEInventoryOut (Man oldParentMan, EntityAI diz, EntityAI newParent)
	{
        GetGame().ObjectDelete(this);
	}  
}
class HRZ_Moderator_Team extends Clothing
{
	override void EEInventoryOut (Man oldParentMan, EntityAI diz, EntityAI newParent)
	{
        GetGame().ObjectDelete(this);
	}  
}
