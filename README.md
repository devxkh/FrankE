# FrankE  [Discontinued]
Frankenstein 3D Engine (MIT) - x64
 - main / rendererthread(Ogre3D)
 - inputmapping (thor/ SDL2)
 - bullet physics
 - networking (enet)
 - entity componentsystem (entityx)
 - simple UI (based on / heavy modified SFGUI)
 - lua scripting (sol2)
 - binary data files (flatbuffer)
 - database (sqlite)
 - sound (FMOD)
 
 ### Building

 use CMakeLists.txt 

 TODO: currently there are still some special [cmake settings](https://github.com/devxkh/FrankE/blob/master/doc/cmakeInfo.txt) necessary

# EDITOR
- [VEX](https://github.com/devxkh/FrankE/blob/master/Editor)  Client/Server Editor(WPF) for FrankE  

# Examples

### Controller Example

can move any entity with an attached body component.

![Example-Controller](https://raw.githubusercontent.com/devxkh/FrankE/master/doc/Screen_XETController_v2.png)

### UI Example

Test ui widgets.
- text input
- button
- label
- layouters (box, alignment)
- image

![UI-Controller](https://raw.githubusercontent.com/devxkh/FrankE/master/doc/Screen_XETUI.png)
