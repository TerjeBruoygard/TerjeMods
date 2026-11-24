modded class Slot
{
	override void SetSeed(ItemBase seed)
	{
		super.SetSeed(seed);
		
		g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Terje_LockSeed, 10, false, seed);
	}
	
	void Terje_LockSeed(ItemBase seed)
	{
		seed.LockToParent();
	}
}
