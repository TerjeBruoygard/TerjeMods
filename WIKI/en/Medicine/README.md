# TerjeMedicine

Medical overhaul mod for DayZ.

![image](/WIKI/logos/TerjeMedicine.jpg)


## DESCRIPTION

This mod introduces a deeper and more realistic health system to the game, enhancing your immersion in the dangers of survival across the vast landscapes of DayZ. Every illness and injury now progresses through distinct stages, each with specific symptoms and treatment methods. Explore and master new mechanics to maintain your health and avoid the dangers lurking at every turn. Each symptom and disease demands a unique treatment approach. The mod features a wide array of medications, tools, and diagnostic methods, ranging from simple bandaging to complex surgical procedures. **Test your survival skills on a new level. Monitor your character's condition to prevent diseases and infections from breaking you!**

## COMPONENTS

Mechanics included in the mod:

1. **PROPHYLAXIS AND TREATMENT**
   + [Medicines](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-medicines)
   + [Vaccines](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-vaccines)
   + [Disinfection](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-disinfection)
     
2. **PHYSICAL CONDITION**
   + [Hematomas](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-hematomas)
   + [Gunshot Wounds](https://github.com/TerjeBruoygard/TerjeMods/edit/master/WIKI/en/Medicine/README.md#-----internal-organ-gunshot-and-stab-wounds)
   + [Stab Wounds](https://github.com/TerjeBruoygard/TerjeMods/edit/master/WIKI/en/Medicine/README.md#-----internal-organ-gunshot-and-stab-wounds)
   + [Internal Organ Wound](https://github.com/TerjeBruoygard/TerjeMods/edit/master/WIKI/en/Medicine/README.md#-----internal-organ-gunshot-and-stab-wounds)
   + [Surgical Sutures](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-surgical-sutures)
   + [Concussion](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-concussion)
   + [Hemostasis](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-hemostasis)
   + [Hematopoiesis](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-hematopoiesis-blood-regeneration)

3. **INFECTIONS AND DISEASES**
   + [Cold](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-cold--pneumonia)
   + [Food Poisoning](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-food-poisoning)
   + [Chemical Poisoning](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-chemical-poisoning)
   + [Zombie Virus](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-zombie-virus)
   + [Sepsis](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-sepsis)
   + [Rabies](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-rabies)

4. **SYMPTOMS**
   + [Pain](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-pain)
   + [Overdose](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-overdose)

5. **EMOTIONAL STATES**
   + [Sleep](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-sleep)
   + [Mental Health](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-mental-health)

6. **ZONES**
   + [Psionic Zones](https://github.com/TerjeBruoygard/TerjeMods/edit/master/WIKI/en/Medicine/README.md#-psionic-zone)

# PROPHYLAXIS AND TREATMENT

## ![image](/WIKI/images/tablets.png) MEDICINES

>Medicines are divided into three categories: tablets, ampoules, and injectors. Tablets are typically used in the early stages of illness and for prevention, with each package containing ten tablets, and packages of the same type can be combined. Ampoules hold potent medications for treating complex illnesses or diseases in their medium to severe stages, requiring players to use a syringe for administration. After each injection, the syringe becomes contaminated and must be disinfected with alcohol or boiled in a pot of water over a fire. Injectors function similarly to ampoules but do not require syringes, as all injectors are disposable.

## ![image](/WIKI/images/vaccine.png) VACCINES

>Vaccines provide protection against dangerous diseases, significantly reducing the risk of infection. Upon use, a vaccine builds immunity to specific infections, helping the character avoid illnesses in contaminated environments. To ensure optimal protection, administer vaccines in advance to boost the character's immunity and regularly monitor the need for revaccination.

| Name       | Item                      | Stage   | Form and Packaging | Duration (s) | Overdose |
|:----------:|:-------------------------:|:-------:|:-------------------:|:------------:|:--------:|
| Vaxicam    | TerjeAmpouleVaxicam       | Vaccine | Ampoule             | 14400        | 0.8      |
| Zerivax    | TerjeAmpouleZerivax       | Vaccine | Ampoule             | 7200         | 1.5      |
| Rabivax    | TerjeAmpouleRabivax       | Vaccine | Ampoule             | 14400        | 1.3      |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medInfluenzaVacineTimeSec  = 14400; // Vaccine against Cold
    medZVirusVacineTimeSec     = 7200;  // Vaccine against Z Virus
    medRabiesVacineTimeSec     = 14400; // Vaccine against Rabies
```

## ![image](/WIKI/images/desinfection.png) DISINFECTION

>Disinfection is a mandatory procedure for maintaining sterility and preventing wound infections. Dirty medical items must be thoroughly disinfected before use to minimize the risk of infection. Prior to any medical procedures or operations, hands should also be disinfected, especially in field conditions where the risk of infection is higher. Proper disinfection is essential for successful treatment and ensuring health safety in extreme environments.

| Name                      | Item                 | Stage        |
|:-------------------------:|:--------------------:|:------------:|
| Alcoholic Tincture        | DisinfectantAlcohol  | Disinfection |
| Disinfectant Spray        | DisinfectantSpray    | Disinfection |

# PHYSICAL CONDITION

## ![image](/WIKI/images/hematoma.png) HEMATOMAS

>Hematomas can occur if you are hit by a zombie or struck with blunt weapons. When numerous hematomas are present, your health will begin to decline. Although they heal naturally over time, applying ointments can speed up the healing process.

| Name        | Item                  | Form and Packaging | Duration (s) | Overdose |
|:-----------:|:---------------------:|:-------------------:|:------------:|:--------:|
| Viprosal    | TerjeSalveViprosal    | Tube of ointment    | 300          | 0.0      |
| Capsicum    | TerjeSalveCapsicum    | Tube of ointment    | 400          | 0.0      |
| Finalgon    | TerjeSalveFinalgon    | Tube of ointment    | 600          | 0.0      |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medHematomaHeal=1; // Strength
    medHematomaHealTimeSec=400; // Duration (s)
```


## ![image](/WIKI/images/organs.png)  ![image](/WIKI/images/bullet.png)  ![image](/WIKI/images/cut3.png) INTERNAL ORGAN, GUNSHOT AND STAB WOUNDS

>A player can sustain a piercing wound from melee attacks or a bullet wound from firearms, both of which can cause severe bleeding and require immediate bandaging. Hemostatic bandages are more effective than regular bandages or cloth. After bandaging, the wound may continue to bleed slightly until the foreign object is removed with a surgery. In more severe cases, these wounds can lead to internal organ injuries, which are deeper and more difficult to treat. A well-maintained bulletproof vest can protect against bullet wounds, and its effectiveness is determined by a ballistic calculator. Light vests can block small-caliber rounds but are ineffective against medium and large calibers. If the vest successfully blocks the bullet, the player will still sustain an unarmored wound in the form of a hematoma.

| Name                        | Item                             | Form and Packaging | Volume | Internal Organs (strength/time) | Bullet (strength/time) | StubEffectivity (strength/time) | 
|:---------------------------:|:--------------------------------:|:-------------------:|:------:|:-------------------------------:|:---------------------:|:--------------------------------:|
| Medical Bowl with Instrument (Ceramic)| TerjeSurgicalTool_Ceramic        | Surgical tools     | 1      | 0.05/90                         | 0.2/40                | 0.4/30                           |
| Medical Bowl with Instrument (White)  | TerjeSurgicalTool_White          | Surgical tools     | 1      | 0.05/90                         | 0.2/40                | 0.4/30                           |
| Field Surgical Kit                   | TerjeSurgicalKit                 | Surgical kit       | 5      | 0.2/40                          | 0.5/25                | 0.7/20                           |
| IFAK                        | TerjeFirstAidKitIndividual_Black | Universal kit      | 10     | 0.3/40                          | 0.6/30                | 0.8/20                           |
| AFAK                        | TerjeFirstAidKitAdvance_Black    | Universal kit      | 20     | 0.3/40                          | 0.6/30                | 0.8/20                           |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
	medBloodStop=3;
	medBloodHemostaticValue=3;
	medBloodHemostaticTimeSec=60; // Duration (s)
	terjeSurgeryKitRefill=1;
	terjeSurgeryVisceraEffectivity=0.3; // Chance to heal
	terjeSurgeryVisceraTime=40; // Duration (s)
	terjeSurgeryBulletEffectivity=0.6; // Chance to heal
	terjeSurgeryBulletTime=30; // Duration (s)
	terjeSurgeryStubEffectivity=0.8; // Chance to heal
	terjeSurgeryStubTime=20; // Duration (s)
```

## ![image](/WIKI/images/cut2.png) SURGICAL SUTURES

>Surgical sutures are applied during surgery and must be regularly disinfected to prevent sepsis. Proper hygiene and disinfection are essential to ensure successful healing and reduce the risk of life-threatening infections.

| Name                      | Item                             | Form and Packaging | Volume | Internal Organs (strength/time) | Bullet (strength/time) | StubEffectivity (strength/time) | 
|:-------------------------:|:--------------------------------:|:-------------------:|:------:|:-------------------------------:|:---------------------:|:--------------------------------:|
| Medical Bowl with Instrument (Ceramic) | TerjeSurgicalTool_Ceramic      | Surgical tools     | 1      | 0.05/90                         | 0.2/40                | 0.4/30                           |
| Medical Bowl with Instrument (White) | TerjeSurgicalTool_White        | Surgical tools     | 1      | 0.05/90                         | 0.2/40                | 0.4/30                           |
| Field Surgical Kit                  | TerjeSurgicalKit               | Surgical kit       | 5      | 0.2/40                          | 0.5/25                | 0.7/20                           |
| IFAK                       | TerjeFirstAidKitIndividual_Black | Universal kit      | 10     | 0.3/40                          | 0.6/30                | 0.8/20                           |
| AFAK                       | TerjeFirstAidKitAdvance_Black  | Universal kit      | 20     | 0.3/40                          | 0.6/30                | 0.8/20                           |

## ![image](/WIKI/images/brain.png) CONCUSSION

>A concussion can result from a strong blow to the head with a blunt object, an explosion near the character, or a low-caliber bullet impact while wearing a ballistic helmet. Initial symptoms include headache, dizziness, unstable coordination, and blurred vision, all of which can hinder movement and combat effectiveness. While a concussion gradually subsides on its own, recovery can be accelerated with special medications that reduce symptom severity.

Name  | Item | Stage | Level | Form and Packaging | Duration (sec) | Overdose |
|:-----------:|:-----------:|:-----------:|:-----:|:---------:|:-------------:|:------------------:|
|  Noopept  | TerjePillsNoopept | Treatment | -   |   Tablets  |      380      |         0.35        |
|   Neirox  | TerjeAmpouleNeirox | Treatment | -   |   Ampoule  |      600      |        0.6        |
|   Neirox  | TerjeInjectorNeirox | Treatment | -  |   Injector  |      500      |        0.3        |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medConcussionHealTimeSec = 300; // Duration (sec)
    overdosedIncrement = 0.3; // Overdose
```

## ![image](/WIKI/images/blood3.png) HEMOSTASIS (BLEEDING RATE)

>Hemostasis is your body’s natural process for stopping bleeding. Your character can slow blood loss by using specific medications, giving you valuable time to survive the injury and seek additional treatment.

| Name              | Item                         | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:-----------------:|:----------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Vikasol           | TerjePillsVikasol           | Treatment |   1    | Tablets            |     300      |   0.15   |
| Erytromixelin     | TerjeInjectorErytromixelin  | Treatment |   3    | Injector           |     300      |   0.32   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item):
```cs
	medBloodHemostaticValue = 1; // Strength
        medBloodHemostaticTimeSec = 300; // Duration (s)
        overdosedIncrement = 0.15; // Overdose increment
```

## ![image](/WIKI/images/blood4.png) HEMATOPOIESIS (BLOOD REGENERATION)

>Hematopoiesis is your body’s process of regenerating red blood cells. Your character can boost the rate of blood regeneration with specific medications, helping you recover more quickly from scratches, cuts, and bullet wounds.

| Name              | Item                         | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:-----------------:|:----------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Irovit            | TerjePillsIrovit             | Treatment |   1   | Tablets            |      120     |   0.3    |
| Magnesium Sulfate | TerjePillsMagnesiumSulfate   | Treatment |   1   | Tablets            |      120     |   0.3    |
| Erythropoetin     | TerjeAmpouleErythropoetin    | Treatment |   1   | Ampoule            |      600     |   0.4    |
| Erythropoetin     | TerjeInjectorErythropoietin  | Treatment |   1   | Injector           |      900     |   0.4    |
| Erytromixelin     | TerjeInjectorErytromixelin   | Treatment |   2   | Injector           |      300     |   0.32   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item):
```cs
	medBloodRegenValue = 1; // Strength
        medBloodRegenTimeSec = 120; // Duration (s)
        overdosedIncrement = 0.3; // Overdose increment
```

# INFECTIONS AND DISEASES

## ![image](/WIKI/images/influenza.png) COLD / PNEUMONIA

>You can catch a cold or the flu from prolonged exposure to cold temperatures. Without proper treatment, a mild cold can progress and eventually develop into pneumonia. When suffering from pneumonia, your character will slowly lose health. Treat it using antibiotics of the same level or higher, with multiple doses often needed for full recovery. A mild cold can be cured by resting in a warm place.

| Name          | Item                     | Stage    | Level | Form and Packaging | Duration (s) | Overdose |
|:-------------:|:------------------------:|:--------:|:-----:|:-------------------:|:------------:|:--------:|
| Tetracycline  | TetracyclineAntibiotics  | Treatment| 1     | Tablets             | 300          | 0.45     |
| Paracetamol   | TerjePillsParacetamol    | Treatment| 1     | Tablets             | 200          | 0.45     |
| Amibaktam     | TerjePillsAmibaktam      | Treatment| 1     | Tablets             | 60           | 0.05    |
| Ibuprofen     | TerjePillsIbuprofen      | Treatment| 2     | Tablets             | 300          | 0.35     |
| Nurofen       | TerjePillsNurofen        | Treatment| 2     | Tablets             | 300          | 0.52     |
| Amoxiclav     | TerjePillsAmoxiclav      | Treatment| 2     | Tablets             | 1200         | 0.75     |
| Piperacillin  | TerjePillsPiperacylin    | Treatment| 2     | Tablets             | 1100         | 0.45     |
| Ketarol       | TerjeAmpouleKetarol      | Treatment| 2     | Ampoule             | 1200         | 0.5      |
| Amoxivan      | TerjeAmpouleAmoxivan     | Treatment| 2     | Ampoule             | 900          | 0.3      |
| Topoisomerase | TerjeInjectorTopoizomeraza| Treatment| 3     | Injector            | 900          | 0.65     |
| Imipenem      | TerjeAmpouleImipenem     | Treatment| 3     | Ampoule             | 900          | 0.7      |
| Flemoclave     | TerjeAmpouleFlemoclav    | Treatment| 3     | Ampoule             | 1200         | 0.8      |
| Amoxiclav     | TerjeInjectorAmoxiclav   | Treatment| 3     | Injector            | 1800         | 0.6      |
| Vaxicam       | TerjeAmpouleVaxicam      | Vaccine  | -     | Ampoule             | 14400        | 0.8      |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medAntibioticLevel = 1; // Strength
    medAntibioticsTimeSec = 300; // Duration (s)
    overdosedIncrement = 0.45; // Overdose
```

## ![image](/WIKI/images/poisoning.png) FOOD POISONING

>Food poisoning can result from consuming spoiled or undercooked food, rotten fruits, poisonous mushrooms, dirty water, or accidentally ingesting substances like gasoline. Symptoms such as nausea and vomiting appear quickly after consumption. If left untreated, the condition can worsen, causing dehydration and gradual health loss. Treatment involves drinking plenty of water and using specific medications to relieve the symptoms.

| Name                | Item                       | Stage   | Level | Form and Packaging | Duration (s) | Overdose |
|:-------------------:|:-------------------------:|:-------:|:-----:|:------------------:|:------------:|:--------:|
| Charcoal  | CharcoalTablets           | Treatment |   1   | Tablets           |      300     |   0.01   |
| Polysorb            | TerjePillsPolisorb        | Treatment |   1   | Tablets           |      300     |   0.05   |
| Phthalazole          | TerjePillsFtalazol        | Treatment |   1   | Tablets           |     1200     |   0.25   |
| Mesalazine          | TerjePillsMesalazin       | Treatment |   2   | Tablets           |      600     |   0.35   |
| Chelating Tablets   | ChelatingTablets          | Treatment |   2   | Tablets           |      600     |   0.6    |
| Metoclopramid      | TerjeAmpouleMetoclopramid | Treatment |   2   | Ampoule           |     1200     |   0.4    |
| Heptral             | TerjeAmpouleHeptral       | Treatment |   3   | Ampoule           |      600     |   0.6    |
| Stomaproxidal       | TerjeInjectorStomaproxidal| Treatment |   3   | Injector          |      900     |   0.68   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medAntipoisonLevel = 1; // Strength
    medAntipoisonTimeSec = 300; // Duration (s)
    overdosedIncrement = 0.45; // Overdose
```

## ![image](/WIKI/images/biohazard.png) CHEMICAL POISONING

>Chemical poisoning occurs from inhaling toxic gases. Early symptoms include coughing, followed by nausea and vomiting as the condition worsens. In its later stages, chemical poisoning leads to severe health loss and can be fatal without timely treatment. To counteract the effects, take an antidote or specific medications designed to reduce toxicity.

| Name             | Item                      | Stage   | Level | Form and Packaging | Duration (s) | Overdose |
|:----------------:|:------------------------:|:-------:|:-----:|:------------------:|:------------:|:--------:|
| Rombiopental     | TerjePillsRombiopental   | Treatment |   1   | Tablets           |       30     |   0.15   |
| Neuroсetal       | TerjeAmpouleNeirocetal   | Treatment |   2   | Ampoule           |      500     |   1.25   |
| AntiChem Injector | AntiChemInjector         | Treatment |   3   | Injector          |      180     |   1.1    |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
	medAntibiohazardLevel = 1; // Strength
	medAntibiohazardTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

## ![image](/WIKI/images/virusz.png) ZOMBIE VIRUS

>The zombie virus is transmitted through airborne droplets and bodily fluids, with a small chance of infection during close combat with zombies. The risk increases significantly if a zombie inflicts wounds on you. Wearing a face mask and ballistic armor can help reduce the likelihood of infection. The virus has a long incubation period, giving players over an hour of real time to find an antidote. In the terminal stage of the infection, your health will begin to rapidly decline.

| Name      | Item                      | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:---------:|:-------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Zivirol   | TerjeAmpouleZivirol       | Treatment |   -   | Ampoule           |     1000     |   2.35   |
| Zivirol   | TerjeInjectorZivirol      | Treatment |   -   | Injector          |     1200     |   2.5    |
| Zerivax   | TerjeAmpouleZerivax       | Vaccine   |   -   | Ampoule           |     7200     |   1.5    |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
	medZAntidotTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
	terjeAddHealth = -20; // Health reduction upon medicine injection
	terjeAddBlood = -10; // Blood reduction upon medicine injection
	terjeAddShock = -100; // Shock reduction upon medicine injection
```

## ![image](/WIKI/images/blood2.png) SEPSIS

>Sepsis occurs when an infection enters an open wound, potentially resulting from a zombie scratch, knife wound, or gunshot wound with a small probability. The risk increases significantly if you handle the wound with dirty hands. If left untreated, sepsis will gradually cause your health to deteriorate over time.

| Name          | Item                        | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:-------------:|:---------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Flemoclav     | TerjeAmpouleFlemoclav       | Treatment |   3   | Ampoule           |     1200     |   0.8    |
| Imipenem      | TerjeAmpouleImipenem        | Treatment |   3   | Ampoule           |      900     |   0.7    |
| Amoxiclav     | TerjeInjectorAmoxiclav      | Treatment |   3   | Injector          |      300     |   0.6    |
| Topoisomerase | TerjeInjectorTopoizomeraza  | Treatment |   3   | Injector          |      600     |   0.65   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
	medAntibioticLevel = 1; // Strength
	medAntisepsisTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

## ![image](/WIKI/images/virus.png) RABIES

>Rabies is transmitted through bites from infected animals, such as wolves. After infection, the disease progresses gradually, with no immediate symptoms. In the early stage, mild temperature fluctuations and weakness occur, often going unnoticed. In the second stage, the condition worsens, causing severe nausea and vomiting, which prevent the character from eating or drinking. In the critical third stage, a spike in temperature leads to rapid health loss, exhaustion, and severely impaired survival. Without timely treatment, the disease is fatal. Early-stage treatment with special medications or vaccination before infection can stop the disease from progressing.

| Name            | Item                      | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:---------------:|:-------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Rifampicin     | TerjeAmpouleRifampicyne  | Treatment |   3   | Ampoule           |      300     |   1.35   |
| Rabinoline      | TerjeAmpouleRabinoline   | Treatment |   2   | Ampoule           |      600     |   0.8    |
| Rabinucoline    | TerjeInjectorRabinucoline| Treatment |   3   | Injector          |      900     |   1.46   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item):
```cs
	medRabiesAntibioticLevel = 1; // Strength
	medRabiesAntibioticTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

# SYMPTOMS

## ![image](/WIKI/images/pain.png) PAIN

>Pain results from various injuries, with its intensity depending on the severity of the trauma. Although pain gradually subsides on its own over time, it can be relieved more quickly by using painkillers of the corresponding level or higher.

| Name             | Item                      | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:----------------:|:-------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Codeine          | PainkillerTablets         | Treatment |   1   | Tablets           |      300     |   0.2    |
| Analgin          | TerjePillsAnalgin         | Treatment |   1   | Tablets           |      500     |   0.15   |
| Nimesulide        | TerjePillsNimesulid       | Treatment |   1   | Tablets           |      600     |   0.25   |
| Paracetamol      | TerjePillsParacetamol     | Treatment |   1   | Tablets           |      200     |   0.45   |
| Ibuprofen        | TerjePillsIbuprofen       | Treatment |   1   | Tablets           |      600     |   0.35   |
| Nurofen          | TerjePillsNurofen         | Treatment |   1   | Tablets           |      350     |   0.52   |
| Noopept          | TerjePillsNoopept         | Treatment |   1   | Tablets           |      380     |   0.35   |
| Ketarol          | TerjeAmpouleKetarol       | Treatment |   1   | Ampoule           |     1200     |   0.5    |
| Novacaine        | TerjeAmpouleNovacaine     | Treatment |   2   | Ampoule           |     1200     |   0.4    |
| Morphinocin         | TerjeAmpouleMorphine      | Treatment |   3   | Ampoule           |      850     |   0.52   |
| Hexobarbital     | TerjeAmpouleGexobarbital  | Treatment |   3   | Ampoule           |      900     |   0.65   |
| Reanimatal       | TerjeInjectorReanimatal   | Treatment |   3   | Injector          |      240     |   1.85   |
| Propital       | TerjeInjectorPropital   | Treatment |   2   | Injector          |      180     |   0.75   |
| Morphine         | Morphine                  | Treatment |   3   | Injector          |      300     |   0.75   |
| Promidol         | TerjeInjectorPromidol     | Treatment |   3   | Injector          |      600     |   0.45   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item):
```cs
	medPainkillerLevel = 1; // Strength
	medPainkillerTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

## ![image](/WIKI/images/overdose.png) OVERDOSE

>Overdose occurs when excessive amounts of medication or toxic substances are introduced into the body.  
The overdose gradually weakens as toxins are eliminated from the system. It progresses through three stages:  

>**First stage:** The character experiences nausea and hallucinations, losing clarity of perception.  

>**Second stage:** The condition worsens, and the character may lose consciousness, becoming vulnerable to the environment.  

>**Third stage:** Critical health deterioration occurs, threatening the character's life.  

| Name          | Item          | Stage   | Level | Form and Packaging | Duration (s) | Overdose |
|:-------------:|:-------------:|:-------:|:-----:|:------------------:|:------------:|:--------:|
| Water         | WaterBottle   | Treatment |   1   | Bottle            |      300     |   0.0    |

# EMOTIONAL STATES

## ![image](/WIKI/images/dream.png) SLEEP

>Your character now needs sleep, just like food and water. Regular rest is essential for maintaining health and stamina.  
If the sleep indicator turns yellow, the character will start yawning, and their vision will gradually worsen.  
When the indicator reaches the red level, the character may lose consciousness from exhaustion. Warm places are ideal for sleeping — near a fireplace, in a tent, inside a house, or in a sleeping bag. Sleep is impossible if the character is freezing, starving, or suffering from serious health problems (stage two illnesses and above). During sleep, the character rapidly restores health and blood, and has a chance to recover from mild illnesses, such as stage one flu. Sleeping bags provide extra warmth and comfort, making sleep safer and more effective in harsh conditions.  


| Name               | Item                | Stage          | Level | Form and Packaging | Duration (s) | Overdose |
|:------------------:|:------------------:|:--------------:|:-----:|:------------------:|:------------:|:--------:|
| MadBull® Energy Drink     | TerjeDrinkMadBull  | Recovery       |   8   | Bottle            |      1.0     |   0.0    |
| Gang® Energy Drink        | TerjeDrinkGang     | Recovery       |   6   | Bottle            |      1.0     |   0.0    |
| Yaguar® Energy Drink      | TerjeDrinkYaguar   | Recovery       |  10   | Bottle            |      1.0     |   0.0    |
| PrayBoy® Energy Drink     | TerjeDrinkPrayboy  | Recovery       |   4   | Bottle            |      1.0     |   0.0    |
| 6Energy® Energy Drink      | TerjeDrink6Energy  | Recovery       |   8   | Bottle            |      0.8     |   0.0    |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item):
```cs
	medSleepingIncrementValue = 8; // Strength
	medSleepingIncrementTimeSec = 0.8; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

## ![image](/WIKI/images/mental.png) MENTAL HEALTH

>The character's mental health can deteriorate under extreme stress, such as zombie attacks, prolonged exposure to dangerous Psi-zones, or consuming human meat, which can lead to nervous breakdowns and hallucinations. These conditions may trigger panic and disorientation, making survival and interaction with the environment more challenging. To manage these symptoms, use antidepressants to stabilize the character's psyche and mitigate the negative effects of stress.  


| Name              | Item                         | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:-----------------:|:----------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Adepress          | TerjePillsAdepress          | Treatment |   1   | Tablets           |      150     |   0.2    |
| Agteminol         | TerjePillsAgteminol         | Treatment |   1   | Tablets           |      120     |   0.2    |
| Venlafaxine       | TerjePillsVenlafaxine       | Treatment |   1   | Tablets           |      250     |   0.3    |
| Actaparoxetine    | TerjeAmpouleActaparoxetine  | Treatment |   2   | Ampoule           |      400     |   0.4    |
| Amitriptyline     | TerjeAmpouleAmitriptyline   | Treatment |   3   | Ampoule           |      600     |   0.4    |
| Metralindole      | TerjeAmpouleMetralindole    | Treatment |   2   | Ampoule           |      300     |   0.1    |
| Amfitalicyne      | TerjeInjectorAmfitalicyne   | Treatment |   3   | Injector          |      520     |   0.6    |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item):
```cs
	medAntidepresantLevel = 1; // Strength
	medAntidepresantTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

# ZONES

# 🧠 Psionic Zone

Psionic zones are **dangerous areas with high levels of psychoactive effects** that influence a character's mental health.

## ⚠️ What the effects do:
1. The **Psionic Zone** spreads out in a radius, the closer the character is to its center, the stronger the level of the effect from it.

2. **Psychic Impact**: 
When in the Psionic Zone, the character begins to lose mental health, resulting in:
  - Panic, hallucinations, and other abnormal reactions.
  - Inability to control the character normally.

3. **Critical State**: 
When the mental state reaches zero, the character may kill him/herself or commit other unpredictable actions that can lead to death.

## 🛡️ Psionic Protection
To safely visit Psionic zones, you must use [antidepressants](https://github.com/TerjeBruoygard/TerjeMods/tree/master/WIKI/en/Medicine#-mental-state) to stabilize your mental state.
You can also use **PSI Helm** - **TerjeHeadgearPsiHelm** for protection. The standard protection is 95%.

## 🛡️ Protection by SteamID
In order to assign zone protection to certain players, you need to enable **Core.UseCustomProtectionConfigs** in the **Core.cfg** file at **profiles\TerjeSettings\Core.cfg**.
```cs
Core.UseCustomProtectionConfigs = true;
```
After enabling this parameter, restart the server.

In the **profiles\TerjeSettings\CustomProtection** folder you will see a file named **psionic.txt**.

Here you can specify the SteamIDs of the players you want to protect. Each SteamID should be written on a new line.

#### Example:
```cs
76561190000000000
76561190000000001
76561190000000002
```
---

## ⚙️ Zone Configuration:
- **The intensity and size of the zones** can be customized in [configuration](../Modding/README.md#zones) by setting the hazard level.
- You can create a **protective suit kit** by following [instructions](../Modding/README.md#parameters-protectionbodyvalues-and-protectionbodythresholds).
