modded class Fence
{	
	typename ATTACHMENT_HRZ_CODELOCK = HRZ_CodeLock;

	HRZ_CodeLock GetHRZCodeLock()
	{
		HRZ_CodeLock hrz_GetLock = HRZ_CodeLock.Cast( FindAttachmentBySlotName( ATTACHMENT_SLOT_COMBINATION_LOCK ) );
		return hrz_GetLock;
	}
	
	override bool CanOpenFence()
	{
		if ( HasHinges() && !IsOpened() && !IsLocked() && !IsCodeLocked() )
		{
			return true;
		}
		
		return false;
	}

	override void OnPartDismantledServer( notnull Man player, string part_name, int action_id )
	{
		//Checks for code lock

		ConstructionPart constrution_part = GetConstruction().GetConstructionPart( part_name );

		//check gate state
		if ( constrution_part.IsGate() )
		{
			SetGateState( false );
		}
		
		//check gate state
		if ( constrution_part.IsGate() )
		{
			if ( IsCodeLocked() )
			{
				HRZ_CodeLock hrz_Lock = HRZ_CodeLock.Cast( FindAttachmentBySlotName( ATTACHMENT_SLOT_COMBINATION_LOCK ) );
				hrz_Lock.UnlockServer( player, this );
			}
		}
		
		super.OnPartDismantledServer( player, part_name, action_id );
	}

	override void OnPartDestroyedServer( Man player, string part_name, int action_id, bool destroyed_by_connected_part = false )
	{
		super.OnPartDestroyedServer( player, part_name, action_id );
		
		//check gate state
		ConstructionPart constrution_part = GetConstruction().GetConstructionPart( part_name );
		if ( constrution_part.IsGate() && destroyed_by_connected_part ) //avoids attachment dropping on regular hinges destruction
		{
			//drop regular attachments
			HandleDropAttachment(GetBarbedWire1());
			HandleDropAttachment(GetBarbedWire2());
			HandleDropAttachment(GetCamoNet());
			HandleDropAttachment(GetCombinationLock());
			HandleDropAttachment(GetHRZCodeLock());
			
			//rotate back to place
			if ( IsOpened() )
				CloseFence();
		}
		if ( part_name == "wall_base_down" )
		{
			HandleDropAttachment(GetBarbedWire1());
			HandleDropAttachment(GetCombinationLock());
			HandleDropAttachment(GetHRZCodeLock());
		}
		if ( part_name == "wall_base_up" )
		{
			HandleDropAttachment(GetBarbedWire2());
			HandleDropAttachment(GetCamoNet());
			HandleDropAttachment(GetCombinationLock());
			HandleDropAttachment(GetHRZCodeLock());
		}
		
		SetGateState( CheckGateState() );
		//update visuals (server)
		UpdateVisuals();
	}
	
	override void HandleDropAttachment(ItemBase item)
	{
		BarbedWire wire;
		CombinationLock lock;
		HRZ_CodeLock hrzcodelock;
		if (Class.CastTo(wire,item)) //special barbed wire beh.
		{
			wire.SetMountedState( false );
			GetInventory().DropEntity(InventoryMode.SERVER, this, wire);
		}
		else if (Class.CastTo(lock,item))
		{
			lock.UnlockServer(null,this);
		}
		else if (Class.CastTo(hrzcodelock,item))
		{
			hrzcodelock.UnlockServer(null,this);
		//	GetInventory().DropEntity(InventoryMode.SERVER, this, item);
		}
		else if (item)//generic behaviour
		{
			GetInventory().DropEntity(InventoryMode.SERVER, this, item);
		}
	}
	
	//--- ATTACHMENT & CONDITIONS
	override bool CanReceiveAttachment( EntityAI attachment, int slotId )
	{
		if ( super.CanReceiveAttachment( attachment, slotId ) )
		{
			if ( attachment.Type() == ATTACHMENT_HRZ_CODELOCK )
			{
				if ( !HasHinges() )
				{
					return false;
				}
			}
		}

		return true;
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction( HRZ_ActionCodeLockonEntity );
	}
}