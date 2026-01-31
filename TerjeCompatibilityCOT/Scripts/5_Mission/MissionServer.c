modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		
		GetTerjeRPC().RegisterHandler("JM_COT_SetTerjeValue", this, "OnReceive_JM_COT_SetTerjeValue");
	}
	
	private void OnReceive_JM_COT_SetTerjeValue(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param3<string, float, array<string>> clientData;
		if (!ctx.Read(clientData))
		{
			return;
		}
		
		string id = clientData.param1;
		float value = clientData.param2;
		array< string > guids = clientData.param3;

		JMPlayerInstance instance;
		if ( !GetPermissionsManager().HasPermission( "Admin.Player.Set.Health", sender, instance ) )
			return;

		ref TerjeAdmintoolSupport_PlayerStat stat;
		if (!GetTerjeAdmintoolSupport().FindPlayerStat(id, stat))
			return;
		
		if (!stat)
			return;
		
		array< JMPlayerInstance > players = GetPermissionsManager().GetPlayers( guids );
		for ( int i = 0; i < players.Count(); i++ )
		{
			PlayerBase player = PlayerBase.Cast( players[i].PlayerObject );
			if ( !player )
				continue;

			stat.SetValue(player, value);
			GetCommunityOnlineToolsBase().Log( sender, "Set " + stat.GetName() + " To " + value + " [guid=" + players[i].GetGUID() + "]" );
			players[i].Update();
		}
	}
}
