modded class UndergroundStash
{
	private bool m_terjeStashInvisible = false;
	
	override void InitItemVariables()
	{
		super.InitItemVariables();
		RegisterNetSyncVariableBool("m_terjeStashInvisible");
	}
	
	override void EEInit()
	{
		super.EEInit();
		TerjeApplyStashVisibility();
	}
	
	override void OnTerjeStoreSave(TerjeStorageWritingContext ctx)
	{
		super.OnTerjeStoreSave(ctx);
		ctx.WriteBool("hiddenstash", m_terjeStashInvisible);
	}
	
	override void OnTerjeStoreLoad(TerjeStorageReadingContext ctx)
	{
		super.OnTerjeStoreLoad(ctx);
		ctx.ReadBool("hiddenstash", m_terjeStashInvisible);
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		TerjeApplyStashVisibility();
		SetSynchDirty();
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		TerjeApplyStashVisibility();
	}
	
	void SetTerjeStashInvisible(bool state)
	{
		if (g_Game.IsDedicatedServer())
		{
			m_terjeStashInvisible = state;
			TerjeApplyStashVisibility();
			SetSynchDirty();
		}
	}
	
	protected void TerjeApplyStashVisibility()
	{
		SetInvisible(false);
		SetSimpleHiddenSelectionState(0, !m_terjeStashInvisible);
	}
	
	bool GetTerjeStashInvisible()
	{
		return m_terjeStashInvisible;
	}
}