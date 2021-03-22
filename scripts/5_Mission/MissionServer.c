modded class MissionServer
{

	override void OnClientPrepareEvent(PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int preloadTimeout)
	{
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Call(GetGame().AdminLog, "[HRZ] Identify \"" + identity.GetName() + "\" (id=" + identity.GetId() + ") (steamid=" + identity.GetPlainId() + ")");
        super.OnClientPrepareEvent( identity, useDB, pos, yaw, preloadTimeout);
    }

    override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx)
    {
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Call(GetGame().AdminLog, "[HRZ] NewClient \"" + identity.GetName() + "\" (steamid=" + identity.GetPlainId() + ") (pos=" + pos.ToString() + ")");
		if (GetHRZPermissionManager().MemberExists(identity.GetPlainId()))
		{
		} else {
				if (identity.GetPlainId() == ""){}
					else {
							HRZ_PermissionManager pm = GetHRZPermissionManager();
							pm.UpdatePermissionFile();
						 }
		}
        return super.OnClientNewEvent( identity, pos, ctx );
    }

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) 
    {
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Call(GetGame().AdminLog, "[HRZ] OnConnect \"" + identity.GetName() + "\" (steamid=" + identity.GetPlainId() + ") (pos=" + player.GetPosition().ToString() + ")");
		super.InvokeOnConnect(player, identity);

        if (!player) {
            return;
        }

        if (GetHRZPermissionManager().MemberExists(identity.GetPlainId()))
        {     
            auto params = new Param2<ref array<ref HRZMember>, string>(GetHRZPermissionManager().GetMembersForClient(identity.GetPlainId()), identity.GetPlainId());
            GetGame().RPCSingleParam(player, 20200103, params, true, identity);
        }
    }
   
    override void OnClientDisconnectedEvent(PlayerIdentity identity, PlayerBase player, int logoutTime, bool authFailed)
	{
		if (GetHive() && !authFailed && player.IsAlive() && !m_LogoutPlayers.Contains(player))
		{			
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Call(GetGame().AdminLog, "[HRZ] OnDisconnect \"" + identity.GetName() + "\" (steamid=" + identity.GetPlainId() + ") (pos=" + player.GetPosition().ToString() + ")");
		}
        super.OnClientDisconnectedEvent(identity, player, logoutTime, authFailed);
	}
}
