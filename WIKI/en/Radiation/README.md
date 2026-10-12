# TerjeRadiation

A radiation overhaul mod for DayZ.

![image](/WIKI/logos/TerjeRadiation.jpg)

## DESCRIPTION
The mod adds radiation zones and radiation poisoning mechanics, making world exploration more intense and thrilling. While in a zone, your character and their belongings accumulate radiation, leading to radiation sickness.
The closer you are to the center of the zone, the higher the radiation level. Protection requires an anti-radiation suit and detectors to assess the threat. Radiation poisoning reduces health and causes weakness, and it is treated with special medications.
**Test your survival skills on a new level. Keep an eye on your surroundings to prevent radiation sickness from overcoming you!**

## COMPOSITION
Mechanics included in the mod:

+ [Radiation Poisoning](#-radiation-poisoning)
+ [Radiation Zones](#️-radiation-zones)
+ [Decontamination of Items](#-how-to-clean-items)
+ [Dosimeters](#-zone-detection)
+ [Protective Suit](#️-radiation-protection)
+ [Protective Containers](#️-protective-containers)

## ![image](/WIKI/images/radiation.png) RADIATION POISONING

>Radiation poisoning develops when you are in areas with high radiation levels or in contact with contaminated items. Initial symptoms include weakness, nausea, and dizziness. Over time, the character begins to experience bleeding and weakened immunity. In the later stages, radiation poisoning leads to severe health loss and body exhaustion, threatening the character's life.
To treat radiation poisoning, take medications that remove radiation from the body, such as iodine tablets or anti-radiation drugs. Try to avoid radiation zones or use protective equipment to minimize exposure.

Name  | Item | Stage | Level | Form and Packaging | Duration (s) | Overdose |
|:-----------:|:-----------:|:-----------:|:-----:|:---------:|:-------------:|:------------------:|
| B190 ([*TerjeMedicine](#these-medicines-are-only-available-when-using-the-terjemedicine-mod)) | TerjePillsB190 | Treatment |  1   |  Tablets  |      140      |        0.3       |
|   Potassium Iodide ([*TerjeMedicine](#these-medicines-are-only-available-when-using-the-terjemedicine-mod))  | TerjePillsPotassiumIodide | Treatment | 1   |   Tablets  |      60      |        0.2        |
|  Hexacyanoferrate ([*TerjeMedicine](#these-medicines-are-only-available-when-using-the-terjemedicine-mod))  | TerjePillsHexacyanoferrate | Treatment | 1   |   Tablets  |      120      |         0.3        |
|   Mexamine ([*TerjeMedicine](#these-medicines-are-only-available-when-using-the-terjemedicine-mod))  | TerjePillsMexamine | Treatment | 2   |   Tablets  |      25      |        0.75        |
|  Pentacin ([*TerjeMedicine](#these-medicines-are-only-available-when-using-the-terjemedicine-mod))  | TerjeAmpoulePentacin | Treatment | 2   |   Ampoule  |      400      |         0.5        |
|  Carboxyme ([*TerjeMedicine](#these-medicines-are-only-available-when-using-the-terjemedicine-mod)) | TerjeAmpouleCarboxyme | Treatment | 2   |   Ampoule  |      600     |         0.6        |
|   Radioprotector   | TerjeAntiradInjector | Treatment | 3   |   Injector |      600     |         0.75       |

Parameters for [creating your own items](../Modding/README.md#1-based-on-an-item)
```cs
    medAntiradLevel = 1; //Strength
    medAntiradTimeSec = 300; // Duration (s)
    overdosedIncrement = 0.45; // Overdose
```

# ZONES

# ☢️ Radiation Zones

Radiation zones are **dangerous areas with increased radiation levels**, posing a serious threat to survivors' lives.  
Visiting them requires careful preparation and the use of protective equipment.

## ⚠️ How Contamination Works:
1. The **radiation zone** spreads over a radius; the closer the character is to its epicenter, the higher the radiation level.
2. **Radiation accumulates in the body** as a "rad-buffer" when:
   - Being in the radiation zone.
   - Contacting contaminated items.  
3. The **rad-buffer** gradually causes [Radiation Poisoning](#-radiation-poisoning), which develops as radiation accumulates.  
4. **Objects and clothing also become contaminated**:
   - All items in the radiation zone, including vehicles, accumulate radiation.
   - Items worn by the character also become radioactive.

## 🩸 Consequences of Exposure:
- A person **does not die directly from radiation**, but:
  - Severe exposure causes [Radiation Poisoning](#-radiation-poisoning).
  - Mild exposure weakens the body, provoking other ailments.

## 🧽 How to Clean Items:
After leaving the radiation zone, contaminated items and belongings can be decontaminated using:
- **A large amount of clean water**.
- **Soapy solution**.
- **Special chemical agents**.

To prevent contamination, **use protective containers** that keep items inside clean.

## 📟 Zone Detection

- **Radiation Detectors**:  
  Use radiation dosimeters to measure the radiation level in the surrounding area, on contaminated items, and on the character.  
  Detectors have **different sensitivity levels** and detection radii, helping to more accurately determine the level of danger.

### Types of Dosimeters:

1. **"Pripyat" Dosimeter**  
   - Measures radiation in microsieverts per hour (which equals 0.1 mR/h).  
   - Provides the most accurate readings but is limited to a maximum detectable radiation level of **9.999 μSv/h**.  
   - Detection radius: **3 m**.  
   - Note: Maximum value in milliroentgens is **999 mR/h**.

2. **"MKC-01A" Dosimeter**  
   - Measures radiation in milliroentgens per hour.  
   - Less accurate but with an increased detection radius.  
   - Limited to a maximum radiation level of **9,999 mR/h**.  
   - Detection radius: **5 m**.

3. **"CDV 700" Dosimeter**  
   - Measures radiation in milliroentgens per hour.  
   - Maximum radiation level: **5,000 mR/h**.
   - Provides a wide detection radius: **10 m**.  
   - Suitable for detecting zones at a great distance.

4. **Household Dosimeter "DBG-05"**  
   - Measures radiation in milliroentgens per hour.  
   - Limited to a maximum radiation level of **999 mR/h**.  
   - Compact but with a small detection radius: **1.5 m**.  
   - Ideal for use in local spots with low radiation levels.

Each dosimeter is designed for different tasks: from precise measurements in small radii to detecting zones at great distances. Choose a device depending on the situation and threat level.

## 🛡️ Radiation Protection:
To safely visit radiation zones, a **protective suit set** is required:
- 🥽 **Gas mask with built-in filter** or **Gas mask with separate filter** 
- 🧥 **Jacket**  
- 👖 **Pants**  
- 👟 **Boots**  
- 🧤 **Gloves**  
- 🧢 **Hood**

Name  | Item | Protection Level |
|:-----------:|:-----------:|:-----------:|
| Improvised Gas Mask Filter | GasMask_Filter_Improvised | 70% |
| Gas Mask Filter | GasMask_Filter | 90% |
| Military Gas Mask | GasMask | 95% |
| NBC Protective Jacket | NBCJacketBase | 95% |
| NBC Protective Boots | NBCBootsBase | 95% |
| NBC Protective Pants | NBCPantsBase | 95% |
| NBC Protective Hood | NBCHoodBase | 95% |
| NBC Protective Gloves | NBCGloves_ColorBase | 95% |

### Protection System:

The protection system works as follows:

+ On the edge of a radioactive zone, where exposure is weak, a gas mask will suffice.
+ Closer to the center of the zone, where exposure is stronger, a full set of protective suit is required.

>These parameters, as well as which slots must have (or lack) parts of the suit, can be configured using the section [Modding WIKI](../Modding/README.md#TerjeRadiation).

Each body part wearing protection has a certain influence (weight) on the overall radiation protection level. This influence is expressed in percentages distributed among the suit elements.

Influence of body parts on overall protection:

By default, the percentage influence (weight) of protective suit elements is distributed as follows:
```cs
Mask : 41.67% (weight = 2.5)
Body : 16.67% (weight = 1.0)
Legs : 16.67% (weight = 1.0)
Feet : 8.33% (weight = 0.5)
Hands : 8.33% (weight = 0.5)
Head : 8.33% (weight = 0.5)
```
This means that the absence of a gas mask, which has the highest influence (weight) (41.67%), significantly reduces the overall protection level. For example, if the gas mask is missing, the total influence (weight) of the remaining suit parts will be **58.33%** of the total protection.

Examples of protection calculation:

**1st scenario:**
- Gas mask - absent
- NBC Protective Jacket - protection 95%
- NBC Protective Boots - protection 95%
- NBC Protective Pants - protection 95%
- NBC Protective Hood - protection 95%
- NBC Protective Gloves - protection 95%

**Calculation of total protection:**
Total protection of all body parts: (0 + 95 + 95 + 95 + 95 + 95) / 6 = **79.16%**.

However, since the gas mask is missing, which has the greatest influence (weight), the overall protection level needs to be adjusted:

**Final protection: 46.17%**

**2nd scenario:**
- Military Gas Mask - protection 95%
- NBC Protective Jacket - protection 95%
- NBC Protective Boots - protection 95%
- NBC Protective Pants - protection 95%
- NBC Protective Hood - protection 95%
- NBC Protective Gloves - protection 95%

**Calculation of total protection:**
Total protection of all body parts: (95 + 95 + 95 + 95 + 95 + 95) / 6 = **95%**.

Since the suit is fully equipped (100%), no adjustment is needed.

**Final protection: 95%**

#### Method #2 (Optional)

For more fine-tuning you can prescribe protection to certain clothes, depending on the strength of radiation. This distribution will not take into account the standard settings specified in Method #1, but also takes into account the influence (weight) of body parts.

To do this, you will need to override the required clothing through your mod.

See [Modding WIKI](../Modding/README.md#TerjeRadiation) for more information on customization.

## 🗃️ Protective Cargos:
For safe visits to radiation zones, use **protective cargos**. These are containers that prevent radiation accumulation on items stored inside them. They are indispensable for carrying and protecting valuable items when exploring radiation zones.
- 📦 **Radiation Protection Box** — 60 slots  
- 💼 **Radiation Protection Suitcase** — 35 slots  

## 🛡️ Zone Protection (with Player SteamID)
If you want to assign zone protection to some players, you need to enable **Core.UseCustomProtectionConfigs** in the **Core.cfg** file at **profiles\TerjeSettings\Core.cfg**.
```cs
Core.UseCustomProtectionConfigs = true;
```
After enabling this option, restart the server.

A new file called **radiation.txt** will be created in **profiles\TerjeSettings\CustomProtection**.

In this file you can add the SteamIDs of the players you want to be protected. Each SteamID on a new line.

#### Example:
```cs
76561190000000000
76561190000000000
76561190000000000
```

## ⚙️ Settings:
- **The intensity and size of zones** can be configured in the [configuration](../Modding/README.md#zones) to adjust the level of danger. 
- You can create a **set of protective suit** and adjust its protection by following the [instructions](../Modding/README.md#zone-protection).
---

#### *These medicines are only available when using the medicine mod **[TerjeMedicine](https://steamcommunity.com/sharedfiles/filedetails/?id=3359677479)**

