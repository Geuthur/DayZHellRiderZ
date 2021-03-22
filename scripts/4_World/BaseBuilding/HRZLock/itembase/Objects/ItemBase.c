modded class ItemBase extends InventoryItem
{
	bool IsCodeLocked()
	{
		HRZ_CodeLock hrz_Lock = GetHRZLock();
		if ( hrz_Lock )
			return true;
		return false;
	}
		
	HRZ_CodeLock GetHRZLock()
	{
		HRZ_CodeLock hrz_Lock = HRZ_CodeLock.Cast( FindAttachmentBySlotName( "Att_CombinationLock" ) );

		if ( hrz_Lock )
			return hrz_Lock;
		return NULL;
	}
}