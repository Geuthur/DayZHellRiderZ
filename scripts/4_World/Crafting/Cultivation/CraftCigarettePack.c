class HRZ_Cigarette_Pack_Base extends Container_Base
{
	override bool IsContainer()
	{
		return true;
	}

	override bool CanReceiveItemIntoCargo( EntityAI item )
	{
		if (item.IsKindOf("HRZ_Cigarette_Base") || item.IsKindOf("PetrolLighter") || item.IsKindOf("HRZ_Zippo") || item.IsKindOf("HRZ_Joint_Base") )
		{
			return super.CanReceiveItemIntoCargo(item);
		}
		return false;
	}

	override bool CanSwapItemInCargo (EntityAI child_entity, EntityAI new_entity)
	{
		if (new_entity.IsKindOf("HRZ_Cigarette_Base") || new_entity.IsKindOf("PetrolLighter") || new_entity.IsKindOf("HRZ_Zippo") || new_entity.IsKindOf("HRZ_Joint_Base") )
		{
			return super.CanSwapItemInCargo( child_entity, new_entity );
		}
		return false;
	}
}