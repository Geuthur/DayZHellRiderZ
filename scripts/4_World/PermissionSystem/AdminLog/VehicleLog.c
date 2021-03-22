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