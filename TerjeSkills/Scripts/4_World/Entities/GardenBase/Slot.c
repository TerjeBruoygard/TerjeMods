modded class Slot
{
	private PlayerBase m_Player;
	
	void SetPlayer(PlayerBase player)
	{
		m_Player = player;
	}
	
	PlayerBase GetPlayer()
	{
		return m_Player;
	}
}
