class TerjePlayerModifierMind : TerjePlayerModifierBase
{
	private float m_mindLastValue = -1;
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_MIND_ENABLED))
		{
			return;
		}
		
		// Mind visual states
		float mindCurrentValue = player.GetTerjeStats().GetMindValue(); 
		if (m_mindLastValue < 0)
		{
			m_mindLastValue = mindCurrentValue;
		}
		
		int mindTendency = 0;
		int mindLevel = 0;
		float mindDiff = mindCurrentValue - m_mindLastValue;
		if (mindDiff < 0)
		{
			if      (mindDiff > TerjeMedicineConstants.MIND_TENDENCY_MINUS_STAGE1) mindTendency = -1;
			else if (mindDiff > TerjeMedicineConstants.MIND_TENDENCY_MINUS_STAGE2) mindTendency = -2;
			else                                                                   mindTendency = -3;
		}
		else if (mindDiff > 0)
		{
			if      (mindDiff < TerjeMedicineConstants.MIND_TENDENCY_PLUS_STAGE1) mindTendency = 1;
			else if (mindDiff < TerjeMedicineConstants.MIND_TENDENCY_PLUS_STAGE2) mindTendency = 2;
			else                                                                  mindTendency = 3;
		}

		if      (mindCurrentValue < TerjeMedicineConstants.MIND_LEVEL5) mindLevel = 5;
		else if (mindCurrentValue < TerjeMedicineConstants.MIND_LEVEL4) mindLevel = 4;
		else if (mindCurrentValue < TerjeMedicineConstants.MIND_LEVEL3) mindLevel = 3;
		else if (mindCurrentValue < TerjeMedicineConstants.MIND_LEVEL2) mindLevel = 2;
		else                                                            mindLevel = 1;
		
		player.GetTerjeStats().SetMindLevelAndTendency(mindLevel, mindTendency);
		m_mindLastValue = mindCurrentValue;
		
		// Mind action states
		float mindDegradationMod = 0;
		float mindRestorePerSec = 0;
		float mindCriticalDamage = 0;

		int antidepressLevel = 0;
		float antidepressTime = 0;
		if (player.GetTerjeStats().GetAntidepresant(antidepressLevel, antidepressTime))
		{
			if (antidepressTime > 0)
			{
				player.GetTerjeStats().SetAntidepresant(antidepressLevel, antidepressTime - deltaTime);
			}
			else if (antidepressLevel > 0)
			{
				player.GetTerjeStats().SetAntidepresant(0, 0);
			}
		}
		
		if (antidepressLevel > 0)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_MIND_RESTORE_MEDS_PER_SEC, mindRestorePerSec);
			mindRestorePerSec *= (antidepressLevel + 1);
		}
		else
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_MIND_RESTORE_COMMON_PER_SEC, mindRestorePerSec);
		}
		
		float perkIrmindIncMod = 1.0;
		float perkIrmindDecMod = 1.0;
		if (player.GetTerjeSkills())
		{
			float perkIrnmindMod;
			if (player.GetTerjeSkills().GetPerkValue("immunity", "irnmind", perkIrnmindMod))
			{
				perkIrmindIncMod += perkIrnmindMod;
				perkIrmindDecMod -= Math.Clamp(perkIrnmindMod, 0, 1);
			}
		}
		
		int brainAgents = player.GetSingleAgentCount(eAgents.BRAIN);
		if (player.GetAllowDamage() && (brainAgents > 0))
		{
			float brainTransferAgentsModifier = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_MIND_TRANSFER_AGENTS_MODIFIER, brainTransferAgentsModifier);
			player.GetTerjeStats().AddMindDegradation(brainTransferAgentsModifier * perkIrmindDecMod, brainAgents * 5);
			player.RemoveAgent(eAgents.BRAIN);
		}
		
		mindCurrentValue += (mindRestorePerSec * perkIrmindIncMod * deltaTime);
		
		float mindDegradationValue = 0;
		float mindDegradationTime = 0;
		player.GetTerjeStats().GetMindDegradation(mindDegradationValue, mindDegradationTime);
		if (player.GetAllowDamage())
		{
			if (mindDegradationTime > 0)
			{
				mindDegradationTime -= deltaTime;
				
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_MIND_DEGRADATION_MODIFIER, mindDegradationMod);
				mindCurrentValue -= (mindDegradationValue * mindDegradationMod * perkIrmindDecMod);
			}
			else
			{
				mindDegradationValue = 0;
				mindDegradationTime = 0;
			}
		}
		else
		{
			mindDegradationValue = 0;
			mindDegradationTime = 0;
		}
		
		player.GetTerjeStats().SetMindValue(mindCurrentValue);
		player.GetTerjeStats().SetMindDegradation(mindDegradationValue, mindDegradationTime);
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		if (mindCurrentValue < TerjeMedicineConstants.MIND_CRITICAL)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_MIND_CRITICAL_DAMAGE, mindCriticalDamage);
			DecreasePlayerHealth(player, TerjeDamageSource.MIND, mindCriticalDamage * deltaTime);
			
			if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
			{
				return;
			}
		}
		
		if (mindCurrentValue < TerjeMedicineConstants.MIND_LEVEL4)
		{
			float laughtChange = 1 - (mindCurrentValue / TerjeMedicineConstants.MIND_LEVEL4);
			if (TerjeEvent(laughtChange * deltaTime * 0.1))
			{
				player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_LAUGHTER);
			}
		}
	}
}
