flatc.exe -c  -o ../../../FrankE/src/include/XEDAL/Objects FBEngineTypes.fbs
flatc.exe -c  -o ../../../FrankE/src/include/XEDAL/Objects FB_Settings.fbs
flatc.exe -c  -o ../../../FrankE/src/src/XEUI/DAL FB_UI_Atlas.fbs
flatc.exe -c  -o ../../../FrankE/src/src/XEUI/DAL FB_UI_StateData.fbs
flatc.exe -c  -o ../../../FrankE/src/TestXE/XETCommon Netmsg.fbs
flatc.exe -c  -o ../../../FrankE/src/TestXE/XETCommon Controllers.fbs
flatc.exe -c  -o ../../src/DAL Netmsg.fbs
flatc.exe -c  -o ../../src/DAL Controllers.fbs

flatc.exe -n  -o ../../../VEX\Modules/Core/VEX.Core.Shared/Generated FBEngineTypes.fbs --gen-onefile
flatc.exe -n  -o ../../../VEX\Modules/Core/VEX.Core.Shared/Generated Netmsg.fbs --gen-onefile
flatc.exe -n  -o ../../../VEX\Modules/Core/VEX.Core.Shared/Generated Controllers.fbs --gen-onefile
flatc.exe -n  -o ../../../VEX\Modules/Core/VEX.Core.Shared/Generated FB_Settings.fbs --gen-onefile
flatc.exe -n  -o ../../../VEX\Modules/Core/VEX.Core.Shared/Generated FB_UI_Atlas.fbs --gen-onefile
flatc.exe -n  -o ../../../VEX\Modules/Core/VEX.Core.Shared/Generated FB_UI_StateData.fbs --gen-onefile
@pause
