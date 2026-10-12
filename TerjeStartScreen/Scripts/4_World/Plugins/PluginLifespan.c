modded class PluginLifespan
{
	protected int GetTerjePersistentBeardMaxLevel(PlayerBase player)
	{
		if (player == null) return 0;
		if (player.GetTerjeProfile() == null) return 0;

		int selectedMax = TerjeMathHelper.ClampInt(player.GetTerjeProfile().GetPersistentBeardLevelSelected(), 0, 3);
		return selectedMax;
	}

	protected LifespanLevel FindTerjePersistentBeardVisualLevel(PlayerBase player, int level)
	{
		if (player == null) return null;

		array<ref LifespanLevel> levels = m_LifespanLevels.Get(player.GetPlayerClass());
		if (levels == null || levels.Count() == 0) return null;

		int clampedLevel = TerjeMathHelper.ClampInt(level, 0, levels.Count() - 1);
		for (int i = 0; i < levels.Count(); i++)
		{
			LifespanLevel candidateLevel = levels.Get(i);
			if (candidateLevel && candidateLevel.GetLevel() == clampedLevel) return candidateLevel;
		}

		if (clampedLevel >= 0 && clampedLevel < levels.Count()) return levels.Get(clampedLevel);
		return null;
	}

	void SetPersistentBeardLevel(PlayerBase player, int level)
	{
		if (player == null) return;

		array<ref LifespanLevel> levels = m_LifespanLevels.Get(player.GetPlayerClass());
		if (levels == null || levels.Count() == 0) return;

		int maxBySettings = GetTerjePersistentBeardMaxLevel(player);
		int maxByModel = levels.Count() - 1;
		int maxLevel = maxBySettings;
		if (maxLevel > maxByModel) maxLevel = maxByModel;

		int selectedLevel = TerjeMathHelper.ClampInt(level, 0, maxLevel);
		LifespanLevel visualLevel = FindTerjePersistentBeardVisualLevel(player, selectedLevel);
		if (visualLevel == null) return;

		SetPlayerLifespanLevel(player, visualLevel);
		m_PlayerCurrentLevel.Set(player, visualLevel);
	}

	void ApplyTerjePersistentBeardVisual(PlayerBase player, int level)
	{
		if (player == null) return;

		LifespanLevel visualLevel = FindTerjePersistentBeardVisualLevel(player, level);
		if (visualLevel == null) return;

		SetPlayerLifespanLevel(player, visualLevel);
		m_PlayerCurrentLevel.Set(player, visualLevel);
	}

	protected int GetTerjePersistentBeardThresholdSeconds(PlayerBase player, int level)
	{
		if (player == null) return 0;

		array<ref LifespanLevel> levels = m_LifespanLevels.Get(player.GetPlayerClass());
		if (levels == null || levels.Count() == 0) return 0;

		int clampedLevel = TerjeMathHelper.ClampInt(level, 0, levels.Count() - 1);
		LifespanLevel visualLevel = levels.Get(clampedLevel);
		if (visualLevel == null) return 0;

		float thresholdMinutes = visualLevel.GetThreshold();
		if (thresholdMinutes < 0) thresholdMinutes = 0;

		return thresholdMinutes * 60;
	}

	void SetPersistentBeardState(PlayerBase player, int level, bool syncShaveTime = false)
	{
		if (player == null) return;

		int selectedLevel = TerjeMathHelper.ClampInt(level, 0, 3);
		if (syncShaveTime)
		{
			int currentPlaytime = 0;
			if (g_Game && g_Game.IsMultiplayer() && g_Game.IsServer()) currentPlaytime = player.StatGet(AnalyticsManagerServer.STAT_PLAYTIME);

			int thresholdSeconds = GetTerjePersistentBeardThresholdSeconds(player, selectedLevel);
			int lastShavedSeconds = currentPlaytime - thresholdSeconds;
			if (lastShavedSeconds < 0) lastShavedSeconds = 0;

			player.SetLastShavedSeconds(lastShavedSeconds);
		}

		SetPersistentBeardLevel(player, selectedLevel);
	}

	override void UpdateLifespan(PlayerBase player, bool force_update = false)
	{
		int previousLevel = -1;
		int previousLastShavedSeconds = -1;
		if (player != null)
		{
			previousLevel = player.GetLifeSpanState();
			previousLastShavedSeconds = player.GetLastShavedSeconds();
		}

		super.UpdateLifespan(player, force_update);
		if (!GetGame() || !GetGame().IsDedicatedServer()) return;
		if (!GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_PBEARD_ENABLED)) return;
		if (player == null || player.GetTerjeProfile() == null) return;

		TerjePlayerProfile profile = player.GetTerjeProfile();
		bool allowShave = GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_PBEARD_ALLOWSHAVE);

		int maxLevel = GetTerjePersistentBeardMaxLevel(player);
		int currentLevel = TerjeMathHelper.ClampInt(player.GetLifeSpanState(), 0, maxLevel);
		if (player.GetLifeSpanState() > maxLevel)
		{
			SetPersistentBeardLevel(player, maxLevel);
			currentLevel = maxLevel;
		}

		if (allowShave)
		{
			int syncedAllowShaveLevel = player.GetLifeSpanState();
			int syncedAllowShaveLastShavedSeconds = player.GetLastShavedSeconds();
			if ((previousLevel != syncedAllowShaveLevel) || (previousLastShavedSeconds != syncedAllowShaveLastShavedSeconds)) player.SyncTerjePersistentBeardVisual();
			return;
		}

		int lockedLevel = TerjeMathHelper.ClampInt(profile.GetPersistentBeardLevelSelected(), 0, maxLevel);
		if (currentLevel != lockedLevel)
		{
			SetPersistentBeardLevel(player, lockedLevel);
		}

		int syncedLevel = player.GetLifeSpanState();
		int syncedLastShavedSeconds = player.GetLastShavedSeconds();
		if ((previousLevel != syncedLevel) || (previousLastShavedSeconds != syncedLastShavedSeconds)) player.SyncTerjePersistentBeardVisual();
	}
}
