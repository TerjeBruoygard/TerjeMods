modded class BleedingSourcesManagerServer
{
	bool TerjeAttemptRemoveBleedingSource(int component)
	{
		int bit = GetBitFromSelectionID(component);
		
		if ( bit == 0 )
		{
			return false;
		}
		
		return RemoveBleedingSource(bit);
	}
	
	override void RemoveMostSignificantBleedingSource()
	{
		if (m_Player.GetTerjeStats())
		{
			if (m_Player.GetTerjeStats().GetStubWounds() > 0)
			{
				m_Player.GetTerjeStats().SetStubWounds(m_Player.GetTerjeStats().GetStubWounds() - 1);
				m_Player.GetTerjeStats().SetBandagesClean(m_Player.GetTerjeStats().GetBandagesClean() + 1);
			}
			else if (m_Player.GetTerjeStats().GetSuturesClean() > 0)
			{
				m_Player.GetTerjeStats().SetSuturesClean(m_Player.GetTerjeStats().GetSuturesClean() - 1);
				m_Player.GetTerjeStats().SetSuturesBandagedClean(m_Player.GetTerjeStats().GetSuturesBandagedClean() + 1);
			}
			else if (m_Player.GetTerjeStats().GetSuturesDirty() > 0)
			{
				m_Player.GetTerjeStats().SetSuturesDirty(m_Player.GetTerjeStats().GetSuturesDirty() - 1);
				m_Player.GetTerjeStats().SetSuturesBandagedClean(m_Player.GetTerjeStats().GetSuturesBandagedClean() + 1);
			}
			else
			{
				super.RemoveMostSignificantBleedingSource();
			}
		}
		else
		{
			super.RemoveMostSignificantBleedingSource();
		}
	}
	
	float TerjeCalculateZoneProtection(string zone, string protection)
	{
		if (zone == "")
		{
			return 0;
		}
		
		if (zone == "Torso")
		{
			return TerjeCalculateAttachmentProtection("Vest", protection) + TerjeCalculateAttachmentProtection("Body", protection);
		}
		
		if (zone == "Head" || zone == "Brain")
		{
			return TerjeCalculateAttachmentProtection("Headgear", protection) + TerjeCalculateAttachmentProtection("Mask", protection);
		}
		
		if (zone == "LeftArm" || zone == "RightArm")
		{
			return TerjeCalculateAttachmentProtection("Body", protection);
		}
		
		if (zone == "LeftHand" || zone == "RightHand")
		{
			return TerjeCalculateAttachmentProtection("Gloves", protection);
		}
		
		if (zone == "LeftLeg" || zone == "RightLeg")
		{
			return TerjeCalculateAttachmentProtection("Legs", protection);
		}
		
		if (zone == "LeftFoot" || zone == "RightFoot")
		{
			return TerjeCalculateAttachmentProtection("Feet", protection);
		}
		
		return 0;
	}
	
	float TerjeCalculateAttachmentProtection(string slotName, string protection)
	{
		ItemBase attachment = m_Player.GetItemOnSlot(slotName);
		if (attachment && !attachment.IsRuined())
		{
			return GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + attachment.GetType() + " Protection " + protection);
		}
		
		return 0;
	}
	
	float TerjeBallisticCalculatorProcess(EntityAI source, string ammo)
	{
		float firearmArmorModifier = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_ARMOR_MODIFIER);
		float firearmBalliscticCalculatorSpeedMod = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_BALLISCTIC_CALCULATOR_SPEED_MOD);
		float firearmBalliscticCalculatorCaliberMod = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_BALLISCTIC_CALCULATOR_CALIBER_MOD);
		float firearmBalliscticCalculatorWeightMod = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_BALLISCTIC_CALCULATOR_WEIGHT_MOD);
		float firearmBalliscticCalculatorAPMod = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_BALLISCTIC_CALCULATOR_A_P_MOD);
		float distanceMod = Math.Clamp(1300 - vector.Distance(source.GetPosition(), m_Player.GetPosition()), 100, 1000) * 0.001;
		float bulletSpeed = GetTerjeGameConfig().ConfigGetFloat( "CfgAmmo " + ammo + " typicalSpeed" ) * 0.1 * firearmBalliscticCalculatorSpeedMod;
		float bulletCaliber = GetTerjeGameConfig().ConfigGetFloat( "CfgAmmo " + ammo + " caliber" ) * firearmBalliscticCalculatorCaliberMod;
		float bulletWeight = GetTerjeGameConfig().ConfigGetFloat( "CfgAmmo " + ammo + " weight" ) * firearmBalliscticCalculatorWeightMod;
		float armorDamage = Math.Max(GetTerjeGameConfig().ConfigGetFloat( "CfgAmmo " + ammo + " DamageApplied Health armorDamage" ), 1) * firearmBalliscticCalculatorAPMod;
		float penetrationCalcModifier = bulletSpeed * bulletCaliber * distanceMod * bulletWeight * armorDamage * firearmArmorModifier;
		
		// Divide damage for crossbow bolts
		if (ammo.LastIndexOf("Bolt") != -1)
		{
			penetrationCalcModifier *= 0.1;
		}
		
		return penetrationCalcModifier;
	}
	
	override void ProcessHit(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos)
	{
		// Remember vanilla bleeding sources count
		int bleedingSourcesCount = GetBleedingSourcesCount();
		
		// Call vanilla hit logic
		super.ProcessHit(damage, source, component, zone, ammo, modelPos);
		
		// Check and remove if exist new vanilla bleeding source added by super.ProcessHit
		if (bleedingSourcesCount != GetBleedingSourcesCount())
		{
			TerjeAttemptRemoveBleedingSource(component);
		}
		
		// Call custom terje logic
		TerjeCustomProcessHit(damage, source, component, zone, ammo, modelPos);
	}
	
	void TerjeCustomProcessHit(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos)
	{
		if ( !m_Player || !m_Player.GetIdentity() || !m_Player.GetTerjeStats() || !m_Player.GetAllowDamage() )
		{
			return;
		}
		
		if (zone == "Brain")
		{
			return; // Disable double-damage
		}
		
		int dummyIndex = ammo.IndexOf("Dummy_");
		if (dummyIndex == 0)
		{
			return;
		}
		
		float perkImpactresMod = 1.0;
		float perkDurleathMod = 1.0;
		float perkSepsisresMod = 1.0;
		if (m_Player.GetTerjeSkills())
		{
			float perkImpactres;
			if (m_Player.GetTerjeSkills().GetPerkValue("immunity", "impactres", perkImpactres))
			{
				perkImpactresMod -= Math.Clamp(perkImpactres, 0, 1);
			}
			float perkDurleath;
			if (m_Player.GetTerjeSkills().GetPerkValue("immunity", "durleath", perkDurleath))
			{
				perkDurleathMod -= Math.Clamp(perkDurleath, 0, 1);
			}
			float perkSepsisres;
			if (m_Player.GetTerjeSkills().GetPerkValue("immunity", "sepsisres", perkSepsisres))
			{
				perkSepsisresMod -= Math.Clamp(perkSepsisres, 0, 1);
			}
		}
		
		bool isInKnockout = false;
		if (m_Player.GetTerjeStats() && m_Player.GetTerjeStats().IsInKnockout())
		{
			isInKnockout = true;
		}
		
		bool playerTakeDammage = false;
		typename ammoTypename = ammo.ToType();
		int finisherType = GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_KNOCKOUT_FINISHER_MODE);
		string ammoType = GetTerjeGameConfig().ConfigGetTextOut( "CfgAmmo " + ammo + " DamageApplied type" );
		if (source && source.IsZombie())
		{
			bool zombieDammageNoStamina = GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ZOMBIE_DAMMAGE_NO_STAMINA);
			float zombieDammagePlayerInBlock = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ZOMBIE_DAMMAGE_PLAYER_IN_BLOCK);
			if (m_Player.IsStayingInBlock())
			{
				if (TerjeEventInverse(zombieDammagePlayerInBlock))
				{
					playerTakeDammage = true;
				}
				else if (zombieDammageNoStamina && m_Player.GetStaminaHandler() && m_Player.GetStaminaHandler().GetStaminaNormalized() < 0.05)
				{
					playerTakeDammage = true;
				}
			}
			else
			{
				playerTakeDammage = true;
			}
			
			if (playerTakeDammage && TerjeEventInverse(TerjeCalculateZoneProtection(zone, "melee")))
			{
				playerTakeDammage = false;
			}
			
			if (!isInKnockout && TerjeOverrideProcessHit_Zombie(damage, source, component, zone, ammo, modelPos, playerTakeDammage) && playerTakeDammage)
			{
				float zombieDammageHematomaChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ZOMBIE_DAMMAGE_HEMATOMA_CHANCE);
				float zombieDammageBleedChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ZOMBIE_DAMMAGE_BLEED_CHANCE);
				float zombieDammageContusionChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ZOMBIE_DAMMAGE_CONTUSION_CHANCE);
				float zombieDammageStubWoundChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ZOMBIE_DAMMAGE_STUB_WOUND_CHANCE);
				float zombieDammageHematomaVirusChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ZOMBIE_DAMMAGE_HEMATOMA_VIRUS_CHANCE);
				float zombieDammageBleedVirusChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ZOMBIE_DAMMAGE_BLEED_VIRUS_CHANCE);
				float zombieDammageStubWoundVirusChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ZOMBIE_DAMMAGE_STUB_WOUND_VIRUS_CHANCE);
				
				float perkZmbvirresMod = 1.0;
				if (m_Player.GetTerjeSkills())
				{
					float perkZmbvirres;
					if (m_Player.GetTerjeSkills().GetPerkValue("immunity", "zmbvirres", perkZmbvirres))
					{
						perkZmbvirresMod -= Math.Clamp(perkZmbvirres, 0, 1);
					}
				}
				
				if (TerjeEvent(zombieDammageHematomaChance * perkImpactresMod))
				{
					m_Player.GetTerjeStats().SetHematomas(m_Player.GetTerjeStats().GetHematomas() + 1);
					
					if (m_Player.IsFaceBlocked(false))
					{
						zombieDammageHematomaVirusChance = zombieDammageHematomaVirusChance * 0.25;
					}
					
					if (TerjeEvent(zombieDammageHematomaVirusChance * perkZmbvirresMod))
					{
						m_Player.GetTerjeStats().SetZVirusValue(m_Player.GetTerjeStats().GetZVirusValue() + 0.1);
					}
				}
				
				if (zone == "Head" && TerjeEvent(zombieDammageContusionChance * perkImpactresMod))
				{
					m_Player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_LIGHT);
				}
				
				if (TerjeEvent(zombieDammageBleedChance * perkDurleathMod))
				{
					AttemptAddBleedingSource(component);
					
					if (TerjeEvent(zombieDammageBleedVirusChance * perkZmbvirresMod))
					{
						m_Player.GetTerjeStats().SetZVirusValue(m_Player.GetTerjeStats().GetZVirusValue() + 0.1);
					}
				}
				
				if (TerjeEvent(zombieDammageStubWoundChance * perkDurleathMod))
				{
					m_Player.GetTerjeStats().SetStubWounds(m_Player.GetTerjeStats().GetStubWounds() + 1);
					
					if (TerjeEvent(zombieDammageStubWoundVirusChance * perkZmbvirresMod))
					{
						m_Player.GetTerjeStats().SetZVirusValue(m_Player.GetTerjeStats().GetZVirusValue() + 0.5);
					}
				}
			}
			
			if (isInKnockout && playerTakeDammage && (finisherType == 0))
			{
				m_Player.GetTerjeStats().IncrementKnockoutFinisher();
			}
			
			float mindDegradationValue;
			float mindDegradationTime;
			if (GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ZOMBIE_ATTACK_MIND_DEGRADATION_VALUE, mindDegradationValue) && GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ZOMBIE_ATTACK_MIND_DEGRADATION_TIME, mindDegradationTime))
			{
				m_Player.GetTerjeStats().AddMindDegradation(mindDegradationValue, mindDegradationTime);
			}
			
			return;
		}
		else if (ammo == "Bullet_Expansion_Taser" || (ammoTypename && ammoTypename.IsInherited(Nonlethal_Base)))
		{
			if (TerjeEventInverse(TerjeCalculateZoneProtection(zone, "melee")))
			{
				playerTakeDammage = true;
			}
			
			if (!isInKnockout && TerjeOverrideProcessHit_Nonlethal(damage, source, component, zone, ammo, modelPos, playerTakeDammage) && playerTakeDammage)
			{
				m_Player.GetTerjeStats().SetHematomas(m_Player.GetTerjeStats().GetHematomas() + 1);
			}
			
			return;
		}
		else if (ammo == "BearTrapHit")
		{
			playerTakeDammage = true;
			if (!isInKnockout && TerjeOverrideProcessHit_BearTrap(damage, source, component, zone, ammo, modelPos, playerTakeDammage) && playerTakeDammage)
			{
				m_Player.GetTerjeStats().SetStubWounds(m_Player.GetTerjeStats().GetStubWounds() + 1);
				
				float bearTrapSepsisChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BEAR_TRAP_SEPSIS_CHANCE);
				if (TerjeEvent(bearTrapSepsisChance * perkSepsisresMod))
				{
					m_Player.GetTerjeStats().SetSepsisValue(m_Player.GetTerjeStats().GetSepsisValue() + 0.1);
				}
			}
		}
		else if (ammo == "BarbedWireHit")
		{
			if (TerjeEvent(0.2))
			{
				playerTakeDammage = true;
			}
			
			if (!isInKnockout && TerjeOverrideProcessHit_BarbedWire(damage, source, component, zone, ammo, modelPos, playerTakeDammage) && playerTakeDammage)
			{
				AttemptAddBleedingSource(component);
				m_Player.GetTerjeStats().SetPainValue(m_Player.GetTerjeStats().GetPainValue() + 0.05);
				
				float barbedWireSepsisChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BARBED_WIRE_SEPSIS_CHANCE);
				if (TerjeEvent(barbedWireSepsisChance * perkSepsisresMod))
				{
					m_Player.GetTerjeStats().SetSepsisValue(m_Player.GetTerjeStats().GetSepsisValue() + 0.1);
				}
			}
		}
		else if (ammoType == "Melee")
		{
			bool meleeDammageNoStamina = GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_MELEE_DAMMAGE_NO_STAMINA);
			float meleeDammagePlayerInBlock = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_MELEE_DAMMAGE_PLAYER_IN_BLOCK);
			float bleedThreshold = GetTerjeGameConfig().ConfigGetFloat( "CfgAmmo " + ammo + " DamageApplied bleedThreshold" );
			float bleedIntensity = GetTerjeGameConfig().ConfigGetFloat( "CfgAmmo " + ammo + " DamageApplied Blood damage" );
			bleedThreshold = Math.Clamp(bleedThreshold, 0, bleedIntensity * 0.01);
			
			if (m_Player.IsStayingInBlock() && bleedThreshold < 1)
			{
				if (TerjeEventInverse(meleeDammagePlayerInBlock))
				{
					playerTakeDammage = true;
				}
				else if (meleeDammageNoStamina && m_Player.GetStaminaHandler() && m_Player.GetStaminaHandler().GetStaminaNormalized() < 0.05)
				{
					playerTakeDammage = true;
				}
			}
			else
			{
				playerTakeDammage = true;
			}
			
			if (playerTakeDammage && TerjeEventInverse(TerjeCalculateZoneProtection(zone, "melee")))
			{
				playerTakeDammage = false;
			}
			
			if (source)
			{
				bool meleeHeadshot = (zone == "Head" || zone == "Brain");
				bool executeMeleeWounds = false;
				if (source.IsAnimal())
				{
					if (!isInKnockout)
					{
						executeMeleeWounds = TerjeOverrideProcessHit_Animal(damage, source, component, zone, ammo, modelPos, playerTakeDammage);
					}
					else if (playerTakeDammage && (finisherType == 0))
					{
						m_Player.GetTerjeStats().IncrementKnockoutFinisher();
					}
				}
				else
				{
					if (!isInKnockout)
					{
						executeMeleeWounds = TerjeOverrideProcessHit_Melee(damage, source, component, zone, ammo, modelPos, playerTakeDammage);
					}
					else if (playerTakeDammage && ((finisherType == 0) || (finisherType == 1) || ((finisherType == 2) && meleeHeadshot)))
					{
						m_Player.GetTerjeStats().IncrementKnockoutFinisher();
					}
				}
				
				if (executeMeleeWounds && playerTakeDammage)
				{
					float meleeDammageContusionChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_MELEE_DAMMAGE_CONTUSION_CHANCE);
					float meleeDammageStubWoundChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_MELEE_DAMMAGE_STUB_WOUND_CHANCE);
					float meleeDammageVisceraChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_MELEE_DAMMAGE_VISCERA_CHANCE);
					float meleeDammageSepsisChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_MELEE_DAMMAGE_SEPSIS_CHANCE);
					float meleeDammageHematomaChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_MELEE_DAMMAGE_HEMATOMA_CHANCE);
					bool meleeHeavyAttack = ammo.Contains("Heavy");

					if (bleedThreshold < 0.5)
					{
						if (meleeHeavyAttack || TerjeEvent(meleeDammageHematomaChance * perkImpactresMod))
						{
							m_Player.GetTerjeStats().SetHematomas(m_Player.GetTerjeStats().GetHematomas() + 1);
						}
						
						if (meleeHeadshot)
						{
							if (source.IsMeleeWeapon() && source.IsTwoHandedBehaviour() && TerjeEvent(meleeDammageContusionChance * perkImpactresMod))
							{
								if (meleeHeavyAttack)
								{
									m_Player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_HEAVY);
								}
								else
								{
									m_Player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_LIGHT);
								}
							}
						}
					}
					else
					{
						bool incrementMeleeSepsis = false;
						if (source.IsAnimal() || meleeHeavyAttack || TerjeEvent(meleeDammageStubWoundChance * perkDurleathMod))
						{
							m_Player.GetTerjeStats().SetStubWounds(m_Player.GetTerjeStats().GetStubWounds() + 1);
							incrementMeleeSepsis = true;
							
							if (zone == "Torso" && TerjeEvent(meleeDammageVisceraChance * perkDurleathMod))
							{
								m_Player.GetTerjeStats().SetViscera(true);
							}
							
							AnimalBase animal = AnimalBase.Cast(source);
							if (animal && animal.HasTerjeRabies())
							{
								float rabiesValue = m_Player.GetTerjeStats().GetRabiesValue();
								if (rabiesValue < 0.75)
								{
									m_Player.GetTerjeStats().SetRabiesValue(0.75);
								}
							}
						}
						else
						{
							AttemptAddBleedingSource(component);
							incrementMeleeSepsis = true;
						}
						
						if (incrementMeleeSepsis && TerjeEvent(meleeDammageSepsisChance * perkSepsisresMod))
						{
							m_Player.GetTerjeStats().SetSepsisValue(m_Player.GetTerjeStats().GetSepsisValue() + 0.1);
						}
					}
				}
			}
		}
		else if (ammoType == "Projectile")
		{
			float firearmDammageVisceraChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_DAMMAGE_VISCERA_CHANCE);
			float firearmDammageContusionChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_DAMMAGE_CONTUSION_CHANCE);
			float firearmBulletThroughChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_BULLET_THROUGH_CHANCE);
			float firearmDammageSepsisChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_DAMMAGE_SEPSIS_CHANCE);
			float penetrationCalcModifier = TerjeBallisticCalculatorProcess(source, ammo);
			float firearmProtectionValue = TerjeCalculateZoneProtection(zone, "firearm");
			bool firearmHeadshot = (zone == "Head" || zone == "Brain");
			
			playerTakeDammage = firearmProtectionValue < penetrationCalcModifier;
			if (!isInKnockout && TerjeOverrideProcessHit_Projectile(damage, source, component, zone, ammo, modelPos, playerTakeDammage))
			{
				if (playerTakeDammage)
				{
					if (firearmHeadshot)
					{
						if (TerjeEvent(firearmDammageContusionChance))
						{
							m_Player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_HEAVY);
						}
					}
					else if (zone == "Torso")
					{
						if (TerjeEvent(firearmDammageVisceraChance))
						{
							m_Player.GetTerjeStats().SetViscera(true);
						}
					}
					
					if (TerjeEvent(firearmDammageSepsisChance * perkSepsisresMod))
					{
						m_Player.GetTerjeStats().SetSepsisValue(m_Player.GetTerjeStats().GetSepsisValue() + 0.1);
					}
					
					if (GetTerjeGameConfig().ConfigIsExisting("CfgAmmo " + ammo + " terjeBulletThroughChance"))
					{
						// Override bullet through chance from config
						firearmBulletThroughChance = GetTerjeGameConfig().ConfigGetFloat("CfgAmmo " + ammo + " terjeBulletThroughChance");
					}
					
					if (TerjeEvent(firearmBulletThroughChance))
					{
						m_Player.GetTerjeStats().SetStubWounds(m_Player.GetTerjeStats().GetStubWounds() + 2);
					}
					else
					{
						m_Player.GetTerjeStats().SetStubWounds(m_Player.GetTerjeStats().GetStubWounds() + 1);
						m_Player.GetTerjeStats().SetBulletWounds(m_Player.GetTerjeStats().GetBulletWounds() + 1);
					}
				}
				else
				{
					m_Player.GetTerjeStats().SetHematomas(m_Player.GetTerjeStats().GetHematomas() + 1);
					
					if (firearmHeadshot)
					{
						if (TerjeEvent(firearmDammageContusionChance))
						{
							m_Player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_LIGHT);
						}
					}
				}
			}
			
			if (isInKnockout && playerTakeDammage && ((finisherType == 0) || (finisherType == 1) || ((finisherType == 2) && firearmHeadshot)))
			{
				m_Player.GetTerjeStats().IncrementKnockoutFinisher();
			}
		}
		else if (ammoType == "FragGrenade")
		{
			playerTakeDammage = true;
			if (ammo == "FlashGrenade_Ammo")
			{
				if (!isInKnockout && TerjeOverrideProcessHit_FlashGrenade(damage, source, component, zone, ammo, modelPos, playerTakeDammage) && playerTakeDammage)
				{
					if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FLASHBANG_HEAVY_CONTUSION_CHANCE)))
					{
						m_Player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_HEAVY);
					}
					else if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FLASHBANG_LIGHT_CONTUSION_CHANCE)))
					{
						m_Player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_LIGHT);
					}
				}
			}
			else if (ammo != "Fireworks_Ammo")
			{
				if (!isInKnockout && TerjeOverrideProcessHit_FragGrenade(damage, source, component, zone, ammo, modelPos, playerTakeDammage) && playerTakeDammage)
				{
					if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_EXPLOSION_DAMMAGE_CONTUSION_CHANCE)))
					{
						m_Player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_LIGHT);
					}
					
					int explosionStubsMaxCount = GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_EXPLOSION_DAMMAGE_STUB_MAX);
					for (int stubId = 0; stubId < explosionStubsMaxCount; stubId++)
					{
						if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_EXPLOSION_DAMMAGE_STUB_CHANCE)))
						{
							m_Player.GetTerjeStats().SetStubWounds(m_Player.GetTerjeStats().GetStubWounds() + 1);
						}
					}
					
					int explosionScratchMaxCount = GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_EXPLOSION_DAMMAGE_SCRATCH_MAX);
					if (explosionScratchMaxCount > GetRegisteredSourcesCount())
					{
						explosionScratchMaxCount = GetRegisteredSourcesCount();
					}
					
					for (int scratchBit = 0; scratchBit < explosionScratchMaxCount; scratchBit++)
					{
						if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_EXPLOSION_DAMMAGE_SCRATCH_CHANCE)))
						{
							AttemptAddBleedingSourceDirectly(scratchBit);
						}
					}
				}
				
				if (isInKnockout && playerTakeDammage && (finisherType == 0))
				{
					m_Player.GetTerjeStats().IncrementKnockoutFinisher();
				}
			}
		}
	}
	
	bool TerjeOverrideProcessHit_Zombie(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from zombies.
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return TerjeOverrideProcessHit_FromConfig(damage, source, component, zone, ammo, modelPos, playerTakeDammage);
	}
	
	bool TerjeOverrideProcessHit_Animal(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from animal.
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return TerjeOverrideProcessHit_FromConfig(damage, source, component, zone, ammo, modelPos, playerTakeDammage);
	}
	
	bool TerjeOverrideProcessHit_Melee(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from melee weapon.
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_Projectile(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from projectile (firearm).
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_FragGrenade(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from explosions (grenades).
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_FlashGrenade(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from explosions (grenades).
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_Nonlethal(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from nonlethal ammo (rubber bullets by example).
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_BearTrap(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from bear trap.
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_BarbedWire(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from bear trap.
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_FromConfig(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// You can configure wounds for modded animals and zombies using the TerjeCustomInjuries class in config.cpp
		/*
			class CfgVehicles
			{
				class AnimalBase;
				class YourCustomAnimal: AnimalBase
				{
					class TerjeCustomInjuries
					{
						// Ignore a player's block and armor when calculating a hit hit. (0 = false, 1 = true)
						ignorePlayerBlock=0;
						
						// Overwrite default TerjeMedicine wounds with wounds from the config or not (0 = false, 1 = true)
						overrideDefaultInjueries=1;
						
						// The chance of bleeding on hit (0.0 = 0%, 1.0 = 100%)
						lightBleedingChance=0.0;
						heavyBleedingChance=0.0;
						internalBleedingChance=0.0;
						
						// The chance of hematoma (bruise) on hit (0.0 = 0%, 1.0 = 100%)
						hematomaChance=0.0;
						
						// Chance of concussion (brain contusion) (0.0 = 0%, 1.0 = 100%)
						lightContussionChance=0.0;
						heavyContussionChance=0.0;
						
						// Biohazard (chemical poision)
						chemicalPoisonChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						chemicalPoisonValue=0.0; // Value 1.0 for level 1, 2.0 for level 2 etc...
						
						// Influenza
						influenzaInfectionChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						influenzaInfectionValue=0.0; // Value 1.0 for level 1, 2.0 for level 2 etc...
						
						// Radiation (when you have TerjeRadiation mod)
						radiationChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						radiationValue=0.0; // Value added to the radiation buffer of player
						
						// Zombie virus
						zombieVirusChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						zombieVirusValue=0.0; // Value 1.0 for level 1, 2.0 for level 2 etc...
						
						// Sepsis (blood poisoning)
						sepsisInfectionChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						sepsisInfectionValue=0.0; // Value 1.0 for level 1, 2.0 for level 2 etc...
						
						// Rabies
						rabiesVirusChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						rabiesVirusValue=0.0; // Value 1.0 for level 1, 2.0 for level 2 etc...
						
						// Mind (mental) damage. For Stalker PSI mutants
						psiDamageChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						psiDamageValue=0.0; // Mind damage per second (10 for example)
						psiDamageTimeSec=0.0; // Time of effect in seconds (5 for example)
						
						// Sleeping damage.
						sleepDamageChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						sleepDamageValue=0.0; // Sleeping damage per second (10 for example)
						sleepDamageTimeSec=0.0; // Time of effect in seconds (5 for example)
		
						// Pain
						painChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						painValue=0.0; // Value 1.0 for level 1, 2.0 for level 2 etc...
					};
				};
			};
		*/
		if (g_Game && source && m_Player && m_Player.GetTerjeStats() != null)
		{
			float value;
			string configRoot = "CfgVehicles " + source.GetType() + " TerjeCustomInjuries";
			if (GetTerjeGameConfig().ConfigIsExisting(configRoot))
			{
				if (GetTerjeGameConfig().ConfigGetInt(configRoot + " ignorePlayerBlock") == 1)
				{
					playerTakeDammage = true;
				}
				
				if (playerTakeDammage)
				{
					value = GetTerjeGameConfig().ConfigGetFloat(configRoot + " lightBleedingChance");
					if (value > 0)
					{
						float perkDurleathMod = 1.0;
						if (m_Player.GetTerjeSkills())
						{
							float perkDurleath;
							if (m_Player.GetTerjeSkills().GetPerkValue("immunity", "durleath", perkDurleath))
							{
								perkDurleathMod -= Math.Clamp(perkDurleath, 0, 1);
							}
						}
						
						if (TerjeEvent(value * perkDurleathMod))
						{
							AttemptAddBleedingSource(component);
						}
					}
					
					if (TerjeEvent(GetTerjeGameConfig().ConfigGetFloat(configRoot + " heavyBleedingChance")))
					{
						m_Player.GetTerjeStats().SetStubWounds(m_Player.GetTerjeStats().GetStubWounds() + 1);
					}
					
					if (TerjeEvent(GetTerjeGameConfig().ConfigGetFloat(configRoot + " internalBleedingChance")))
					{
						m_Player.GetTerjeStats().SetViscera(true);
					}
					
					value = GetTerjeGameConfig().ConfigGetFloat(configRoot + " hematomaChance");
					if (value > 0)
					{
						float perkImpactresMod = 1.0;
						if (m_Player.GetTerjeSkills())
						{
							float perkImpactres;
							if (m_Player.GetTerjeSkills().GetPerkValue("immunity", "impactres", perkImpactres))
							{
								perkImpactresMod -= Math.Clamp(perkImpactres, 0, 1);
							}
						}
						
						if (TerjeEvent(value * perkImpactresMod))
						{
							m_Player.GetTerjeStats().SetHematomas(m_Player.GetTerjeStats().GetHematomas() + 1);
						}
					}
					
					if (TerjeEvent(GetTerjeGameConfig().ConfigGetFloat(configRoot + " lightContussionChance")))
					{
						m_Player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_LIGHT);
					}
					
					if (TerjeEvent(GetTerjeGameConfig().ConfigGetFloat(configRoot + " heavyContussionChance")))
					{
						m_Player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_HEAVY);
					}
					
					if (TerjeEvent(GetTerjeGameConfig().ConfigGetFloat(configRoot + " chemicalPoisonChance")))
					{
						m_Player.GetTerjeStats().SetBiohazardValue(m_Player.GetTerjeStats().GetBiohazardValue() + GetTerjeGameConfig().ConfigGetFloat(configRoot + " chemicalPoisonValue"));
					}
					
					if (TerjeEvent(GetTerjeGameConfig().ConfigGetFloat(configRoot + " influenzaInfectionChance")))
					{
						m_Player.GetTerjeStats().SetInfluenzaValue(m_Player.GetTerjeStats().GetInfluenzaValue() + GetTerjeGameConfig().ConfigGetFloat(configRoot + " influenzaInfectionValue"));
					}
					
					if (TerjeEvent(GetTerjeGameConfig().ConfigGetFloat(configRoot + " radiationChance")))
					{
						m_Player.AddTerjeRadiation(GetTerjeGameConfig().ConfigGetFloat(configRoot + " radiationValue"));
					}
					
					value = GetTerjeGameConfig().ConfigGetFloat(configRoot + " zombieVirusChance");
					if (value > 0)
					{
						float perkZmbvirresMod = 1.0;
						if (m_Player.GetTerjeSkills())
						{
							float perkZmbvirres;
							if (m_Player.GetTerjeSkills().GetPerkValue("immunity", "zmbvirres", perkZmbvirres))
							{
								perkZmbvirresMod -= Math.Clamp(perkZmbvirres, 0, 1);
							}
						}
						
						if (TerjeEvent(value * perkZmbvirresMod))
						{
							m_Player.GetTerjeStats().SetZVirusValue(m_Player.GetTerjeStats().GetZVirusValue() + GetTerjeGameConfig().ConfigGetFloat(configRoot + " zombieVirusValue"));
						}
					}
					
					value = GetTerjeGameConfig().ConfigGetFloat(configRoot + " sepsisInfectionChance");
					if (value > 0)
					{
						float perkSepsisresMod = 1.0;
						if (m_Player.GetTerjeSkills())
						{
							float perkSepsisres;
							if (m_Player.GetTerjeSkills().GetPerkValue("immunity", "sepsisres", perkSepsisres))
							{
								perkSepsisresMod -= Math.Clamp(perkSepsisres, 0, 1);
							}
						}
						
						if (TerjeEvent(value * perkSepsisresMod))
						{
							m_Player.GetTerjeStats().SetSepsisValue(m_Player.GetTerjeStats().GetSepsisValue() + GetTerjeGameConfig().ConfigGetFloat(configRoot + " sepsisInfectionValue"));
						}
					}
					
					if (TerjeEvent(GetTerjeGameConfig().ConfigGetFloat(configRoot + " rabiesVirusChance")))
					{
						m_Player.GetTerjeStats().SetRabiesValue(m_Player.GetTerjeStats().GetRabiesValue() + GetTerjeGameConfig().ConfigGetFloat(configRoot + " rabiesVirusValue"));
					}
					
					if (TerjeEvent(GetTerjeGameConfig().ConfigGetFloat(configRoot + " psiDamageChance")))
					{
						m_Player.GetTerjeStats().AddMindDegradation(GetTerjeGameConfig().ConfigGetFloat(configRoot + " psiDamageValue"), GetTerjeGameConfig().ConfigGetFloat(configRoot + " psiDamageTime"));
					}
					
					if (TerjeEvent(GetTerjeGameConfig().ConfigGetFloat(configRoot + " sleepDamageChance")))
					{
						m_Player.GetTerjeStats().AddSleepingDecrement(GetTerjeGameConfig().ConfigGetFloat(configRoot + " sleepDamageValue"), GetTerjeGameConfig().ConfigGetFloat(configRoot + " sleepDamageTime"));
					}
					
					if (TerjeEvent(GetTerjeGameConfig().ConfigGetFloat(configRoot + " painChance")))
					{
						m_Player.GetTerjeStats().SetPainValue(GetTerjeGameConfig().ConfigGetFloat(configRoot + " painValue"));
					}
				}
				
				if (GetTerjeGameConfig().ConfigGetInt(configRoot + " overrideDefaultInjueries") == 1)
				{
					return false;
				}
			}
		}
		
		return true;
	}
}
