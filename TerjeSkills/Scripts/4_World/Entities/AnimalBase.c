modded class AnimalBase
{
	private Particle m_terjeHighlightParticle;
	private bool m_terjeHasReceivedDamage = false;
	private bool m_terjeHasHeadshotDamage = false;
	private bool m_terjeIsExperienceProcessed = false;
	private EntityAI m_terjeLastDamageSource = null;
	private vector m_terjeLastAnimalPos = vector.Zero;
	
	bool HasTerjeReceivedDamage()
	{
		return m_terjeHasReceivedDamage;
	}
	
	bool HasTerjeHeadshotDamage()
	{
		return m_terjeHasHeadshotDamage;
	}
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		m_terjeLastDamageSource = source;
		m_terjeHasReceivedDamage = true;
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (ammo.IndexOf("Dummy_") == 0)
		{
			return;
		}
		
		if (dmgZone == "Zone_Head")
		{
			m_terjeHasHeadshotDamage = true;
		}
		else
		{
			m_terjeHasHeadshotDamage = false;
		}
		
		TerjeHuntingExperienceProcessing(source);
		TerjeHuntingDamageProcessing(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
	
	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);
		
		EntityAI killerEntity = EntityAI.Cast(killer);
		if (killerEntity != null)
		{
			TerjeHuntingExperienceProcessing(killerEntity);
		}
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		if (GetGame().IsClient() && m_terjeHighlightParticle)
		{
			m_terjeHighlightParticle.Stop();
		}
	}
	
	override bool IsTerjeClientUpdateRequired()
	{
		// Only update if player is nearby and has pathfinder perk to reduce performance impact
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player || !player.GetTerjeSkills())
			return false;

		// Check if player has pathfinder perk
		if (player.GetTerjeSkills().GetPerkLevel("hunt", "pathfindr") <= 0)
			return false;

		// Only update animals within reasonable distance
		float distance = vector.Distance(player.GetWorldPosition(), GetWorldPosition());
		return distance <= 200.0; // 200m range for hunting visibility
	}
	
	override void OnTerjeClientUpdate(float deltaTime)
	{
		super.OnTerjeClientUpdate(deltaTime);
		
		if (GetGame().IsClient())
		{
			bool showParticles = false;
			if (IsAlive() && GetTerjeGameConfig().ConfigGetBool("CfgVehicles " + GetType() + " terjeHighlightWithPathfinder"))
			{
				if (m_terjeLastAnimalPos != vector.Zero)
				{
					float distance = vector.Distance(m_terjeLastAnimalPos, GetWorldPosition());
					if (distance >= 2.5)
					{
						PlayerBase localPlayer = PlayerBase.Cast(GetGame().GetPlayer());
						if (localPlayer && localPlayer.GetTerjeSkills() && localPlayer.GetTerjeSkills().GetPerkLevel("hunt", "pathfindr") > 0)
						{
							showParticles = true;
						}
					}
				}
			}
			
			if (showParticles)
			{
				if (!m_terjeHighlightParticle)
				{
					m_terjeHighlightParticle = ParticleManager.GetInstance().PlayOnObject(ParticleList.TERJE_SKILLS_ANIMALS_HIGHLIGHT, this);
				}
			}
			else
			{
				if (m_terjeHighlightParticle)
				{
					m_terjeHighlightParticle.Stop();
					m_terjeHighlightParticle = null;
				}
			}
			
			m_terjeLastAnimalPos = GetWorldPosition();
		}
	}
	
	// We use additional logic to process killer player, because EEKilled method has a bug and from time to time returns self animal as a killer.
	void TerjeHuntingExperienceProcessing(EntityAI killer)
	{
		if (m_terjeIsExperienceProcessed)
		{
			return;
		}
		
		if (IsAlive())
		{
			return;
		}
		
		PlayerBase playerKiller = PlayerBase.Cast(killer);
		if (!playerKiller && killer)
		{
			playerKiller = PlayerBase.Cast(killer.GetHierarchyRootPlayer());
		}
		
		if (!playerKiller && m_terjeLastDamageSource)
		{
			playerKiller = PlayerBase.Cast(m_terjeLastDamageSource.GetHierarchyRootPlayer());
		}
		
		if (playerKiller && playerKiller.IsAlive() && playerKiller.GetTerjeSkills())
		{
			int totalExp = 0;
			float settingModifier;
			if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_KILL_ANIMAL_EXP_GAIN_MODIFIER, settingModifier))
			{
				totalExp += (int)(GetTerjeGameConfig().ConfigGetInt("CfgVehicles " + GetType() + " terjeOnKillHuntingExp") * settingModifier);
			}
			
			if (HasTerjeHeadshotDamage() && GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_HEADSHOT_ANIMAL_EXP_GAIN_MODIFIER, settingModifier))
			{
				totalExp += (int)(GetTerjeGameConfig().ConfigGetInt("CfgVehicles " + GetType() + " terjeOnHeadshotHuntingExp") * settingModifier);
			}
			
			if (totalExp > 0)
			{
				playerKiller.GetTerjeSkills().AddSkillExperience("hunt", totalExp);
				m_terjeIsExperienceProcessed = true;
			}
		}
	}
	
	void TerjeHuntingDamageProcessing(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (!source)
		{
			return;
		}
		
		PlayerBase playerSource = PlayerBase.Cast(source.GetHierarchyRootPlayer());
		if (!playerSource || !playerSource.GetTerjeSkills())
		{
			return;
		}
		
		float additionalDmg = damageResult.GetDamage(dmgZone, "Health");
		string ammoType = GetTerjeGameConfig().ConfigGetTextOut( "CfgAmmo " + ammo + " DamageApplied " + "type" );
		if (ammoType == "Projectile")
		{
			float exphunterPerkValue;
			if (playerSource.GetTerjeSkills().GetPerkValue("hunt", "exphunter", exphunterPerkValue))
			{
				TerjeCommitAdditionalPerkDamage(source, dmgZone, "Dummy_TerjeHuntingProjectile", modelPos, additionalDmg * exphunterPerkValue, 100);
			}
		}
		else if (ammoType == "Melee")
		{
			float knwanatomyPerkValue;
			if (playerSource.GetTerjeSkills().GetPerkValue("hunt", "knwanatomy", knwanatomyPerkValue))
			{
				TerjeCommitAdditionalPerkDamage(source, dmgZone, "Dummy_TerjeHuntingMelee", modelPos, additionalDmg * knwanatomyPerkValue, 100);
			}
		}
	}
	
	void TerjeCommitAdditionalPerkDamage(EntityAI source, string dmgZone, string ammoName, vector modelPos, float damageCoef, int delay)
	{
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.ProcessDirectDamage, delay, false, 0, source, dmgZone, ammoName, modelPos, damageCoef, 0);
	}
}
