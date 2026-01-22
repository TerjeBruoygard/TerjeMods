# 📖 TerjeMods Installation Guide

Welcome! This guide will help you install **TerjeMods** on a **DayZ** server, taking into account their dependencies and specific features. Follow the steps below to ensure the correct operation of the modifications.

---

## List of Mods

**TerjeMods** and their dependencies:  
- **[Terje-Core](https://steamcommunity.com/sharedfiles/filedetails/?id=3649957186)** — the core required for all other mods to function.  
- **[Terje-Medicine](https://steamcommunity.com/sharedfiles/filedetails/?id=3649957536)** — medicine, requires **TerjeCore**.  
- **[Terje-Skills](https://steamcommunity.com/sharedfiles/filedetails/?id=3649958397)** — perks, requires **TerjeCore**.
- **[Terje-StartScreen](https://steamcommunity.com/sharedfiles/filedetails/?id=3649959402)** — start screen, requires **TerjeCore**.
- **[Terje-Radiation](https://steamcommunity.com/sharedfiles/filedetails/?id=3649958757)** - radiation, requires **TerjeCore**.
- **[Terje-CompatibilityCOT](https://steamcommunity.com/sharedfiles/filedetails/?id=3649959707)** — compatibility mod for the *Community Online Tools* admin tool.  
- **[Terje-CompatibilityVPP](https://steamcommunity.com/sharedfiles/filedetails/?id=3649959866)** — compatibility mod for the *Vanilla Plus Plus Admin Tools* admin tool.

> **Important:** For enhanced functionality of perks and medicine, you must install all three mods:  
**TerjeCore**, **TerjeMedicine**, **TerjeSkills**.

---

## Installation via `.bat` File

### Steps:

1. Subscribe to the required mods on the **Steam Workshop** according to the [list of mods](#list-of-mods):

2. Navigate to the `DayZServer` folder where the `DayZServer_x64.exe` file is located.

3. Create or open a `.bat` file (for example, `StartServer.bat`) and add the following lines:

   To install all mods:
   ```bat
   -mod=@CF;@Community-Online-Tools;@TerjeCore;@TerjeCompatibilityCOT;@TerjeMedicine;@TerjeSkills
   ```
4. The final server launch line should look as follows:
   ```bat
   start DayZServer_x64.exe -mod=@CF;@Community-Online-Tools;@TerjeCore;@TerjeCompatibilityCOT;@TerjeMedicine;@TerjeSkills -config=serverDZ.cfg -profiles=./profiles -port=2302
   ```
5. Save the file, perform a [full wipe](#how-to-perform-a-server-wipe) and start the server by running the created (saved) .bat **.bat** file.

## Installation via Hosting Panel

### Steps:

1. Log in to your hosting control panel where your DayZ server is hosted.

2. Go to the mod management section.

3. Install the required mods through the Steam Workshop according to the [list of mods](#list-of-mods)

4. Go to the server settings and check the mod load order. Ensure that the mods are loaded in the correct order. It should look something like this:
    ```cs
    @CF;@Community-Online-Tools;@TerjeCore;@TerjeCompatibilityCOT;@TerjeMedicine;@TerjeSkills 
    ```
5. Save the settings, perform a [full wipe](#how-to-perform-a-server-wipe) and restart the server.

## Installation via OmegaManager Panel

### Steps:

1. Access your OmegaManager panel

2. Select the server, shut it down, and then click **Overview**

3. Open the **Mod Configuration** section:

4. Find and install the required mods according to the [list of mods](#list-of-mods)

5. Arrange the mod load order as follows:
    ```cs
    @CF;@Community-Online-Tools;@TerjeCore;@TerjeCompatibilityCOT;@TerjeMedicine;@TerjeSkills 
    ```
    Then click **Save changes**.

6. Click the **Back** button and then click **install mods**

7. Wait for the mods to install, perform a [full wipe](#how-to-perform-a-server-wipe) of the server, and start the server.

## How to Perform a Server WIPE

1. Shut down the server.

2. Navigate to the **DayZServer/mpmission** folder.

3. Open the folder with your map, for example, **dayzOffline.chernarusplus**.

4. Delete the **storage_1** folder.

5. The wipe is complete, and you can start the server.

## Notes
1. **Updates:** Ensure that all mods are updated to the latest version.

2. **Dependency Check:** Make sure all dependencies are installed correctly.

3. **Server Wipe:** After installing mods, be sure to wipe the server.

## Support

If you have any questions, installation issues, or need recommendations, reach out to us:

- [**Discord**](https://discord.gg/Ec5t3MwnaE) community
- The Issues section on the project's GitHub.


