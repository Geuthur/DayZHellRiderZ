/*class HRZ_Backpack_Canvas_Base extends Clothing
{
    string m_WetTexture = "Client\\clothes\\backpack\\Canvas_Backpack\\data\\canvas_backpack_wet_co.paa";
    string m_WetRvmat = "Client\\clothes\\backpack\\Canvas_Backpack\\data\\canvas_backpack_wet.rvmat";
    string m_RegularTexture = "Client\\clothes\\backpack\\Canvas_Backpack\\data\\canvas_backpack_co.paa";
    string m_RegularRvmat = "Client\\clothes\\backpack\\Canvas_Backpack\\data\\canvas_backpack.rvmat";
    override void SetWet(float value, bool allow_client = false)
    {
        super.SetWet(value,allow_client);
        if(m_VarWet >= 0.25)
        {
            SetObjectTexture(0,m_WetTexture);            
            SetObjectMaterial(0,m_WetRvmat);
        }

        if(m_VarWet < 0.25)
        {
            SetObjectTexture(0, m_RegularTexture);            
            SetObjectMaterial(0, m_RegularRvmat);
        }
    }
    ref array<string> m_AttachmentsLeft = {"WaterBottle"};
    ref array<string> m_AttachmentsRight = {"Hammer", "NailedBaseballBat", "BaseballBat", "Crowbar", "Machete", "Hatchet", "SawedoffMosin9130", "SawedoffIzh18", "SawedoffIzh43Shotgun", "ImprovisedFishingRod" };
    
    override void EEInit(){
		super.EEInit();
        HideUnhideSelection("left_straps_large", 0);
        HideUnhideSelection("left_straps_tight", 1);
        HideUnhideSelection("right_straps_large", 0);
        HideUnhideSelection("right_straps_tight", 1);
        HideUnhideSelection("shoulder_straps_large", 0);
        HideUnhideSelection("shoulder_straps_tight", 1);
	}
    
    override bool CanReceiveAttachment( EntityAI attachment, int slotId )
    {
        if ( attachment.IsKindOf("Crowbar") || attachment.IsKindOf("Machete") || attachment.IsKindOf("Hatchet") || attachment.IsKindOf("BaseballBat") || attachment.IsKindOf("NailedBaseballBat") || attachment.IsKindOf("Hammer") || attachment.IsKindOf("SawedoffMosin9130") || attachment.IsKindOf("SawedoffIzh18") || attachment.IsKindOf("SawedoffIzh43Shotgun") || attachment.IsKindOf("ImprovisedFishingRod") )
        {
            if ( this.FindAttachmentBySlotName("Crowbar") != NULL || this.FindAttachmentBySlotName("Machete") != NULL || this.FindAttachmentBySlotName("Hatchet") != NULL || this.FindAttachmentBySlotName("BaseballBat") != NULL || this.FindAttachmentBySlotName("NailedBaseballBat") != NULL || this.FindAttachmentBySlotName("Hammer") != NULL || this.FindAttachmentBySlotName("SawedoffMosin9130") != NULL || this.FindAttachmentBySlotName("SawedoffIzh18") != NULL || this.FindAttachmentBySlotName("SawedoffIzh43Shotgun") != NULL || this.FindAttachmentBySlotName("ImprovisedFishingRod") != NULL )
            { 
                return false;
            }
        }
        return true;
    }
	
    override bool CanDisplayAttachmentSlot( string slot_name )
    {    
        if (!super.CanDisplayAttachmentSlot(slot_name))
            return false;
        int attachmentId = m_AttachmentsRight.Find(slot_name);
        if (attachmentId > -1)
			return this.FindAttachmentBySlotName(m_AttachmentsRight[attachmentId]) != NULL;
		
        if ( slot_name == "DummySlot" )
            return ( this.FindAttachmentBySlotName("Hammer") == NULL && this.FindAttachmentBySlotName("BaseballBat") == NULL && this.FindAttachmentBySlotName("NailedBaseballBat") == NULL && this.FindAttachmentBySlotName("Hatchet") == NULL && this.FindAttachmentBySlotName("Machete") == NULL && this.FindAttachmentBySlotName("Crowbar") == NULL && this.FindAttachmentBySlotName("SawedoffMosin9130") == NULL && this.FindAttachmentBySlotName("SawedoffIzh18") == NULL && this.FindAttachmentBySlotName("SawedoffIzh43Shotgun") == NULL && this.FindAttachmentBySlotName("ImprovisedFishingRod") == NULL );
        
        return true;
    }

    override void EEItemAttached( EntityAI item, string slot_name )
    {
        super.EEItemAttached( item, slot_name );
        if (m_AttachmentsLeft.Find(slot_name) > -1)
        {            
            HideUnhideSelection("left_straps_tight", 0);
            HideUnhideSelection("left_straps_large", 1);
        }
        if (m_AttachmentsRight.Find(slot_name) > -1)
        {
            HideUnhideSelection("right_straps_tight", 0);
            HideUnhideSelection("right_straps_large", 1);
        }
    }
    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);
        if (m_AttachmentsLeft.Find(slot_name) > -1)
        {
            HideUnhideSelection("left_straps_large", 0);
            HideUnhideSelection("left_straps_tight", 1);
        }       
        if (m_AttachmentsRight.Find(slot_name) > -1)
        {
            HideUnhideSelection("right_straps_large", 0);
            HideUnhideSelection("right_straps_tight", 1);
        }
    }

    void HideUnhideSelection(string selectionName, bool hide = false)
    {
        TStringArray selectionNames = new TStringArray;
        ConfigGetTextArray("simpleHiddenSelections",selectionNames);
        int selectionId = selectionNames.Find(selectionName);  
        SetSimpleHiddenSelectionState(selectionId, hide);
    }
};
*/