modded class ActionGetOutTransport: ActionInteractBase
{
    HRZ_PluginAdminLog m_VehicleAdminLog;
    Transport HRZ_Transport; 

    override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
    {
        HRZ_Transport = null;
		HumanCommandVehicle vehCommand = player.GetCommand_Vehicle();
		if ( vehCommand )
		{
			HRZ_Transport = vehCommand.GetTransport();
        }
        return super.ActionCondition(player, target, item);
    }

    override void OnEndServer(ActionData action_data) {
        super.OnEndServer(action_data);

        m_VehicleAdminLog = HRZ_PluginAdminLog.Cast( GetPlugin(HRZ_PluginAdminLog) );
        m_VehicleAdminLog.HRZ_ActionGetOutTransport(action_data.m_Player, HRZ_Transport);
   }
}

modded class ActionGetInTransport: ActionInteractBase
{
    HRZ_PluginAdminLog m_VehicleAdminLog;
    Transport HRZ_Transport; 

    override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
    {
        HRZ_Transport = null;
        Class.CastTo(HRZ_Transport, target.GetObject());

        if (!super.ActionCondition(player, target, item))        
            return false;        

		ItemBase holdItem = player.GetItemInHands();
		
		if (holdItem) 
        {
            if (holdItem.m_ItemBehaviour == 0 || HRZ_Transport == null)
                return false;

            int crew_index = HRZ_Transport.CrewPositionIndex(target.GetComponentIndex());

            if (crew_index == 0)
                return false;
        }

        return true;
    }

    override void OnEndServer(ActionData action_data) 
    {
        super.OnEndServer(action_data);

        m_VehicleAdminLog = HRZ_PluginAdminLog.Cast( GetPlugin(HRZ_PluginAdminLog) );
        m_VehicleAdminLog.HRZ_ActionGetInTransport(action_data.m_Player, HRZ_Transport);
   }
}