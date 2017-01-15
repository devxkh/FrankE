

function init()

  print("WelcomeState init - start")

  XEngine.graphicsMgr.guiRenderer:loadAtlas("dbData/UI/TestAtlas.fbbin")

  print("WelcomeState init - atlas loaded")
  
-- load this sceneID at init
-- optional param must be set
  XEngine.scene:create(1, nil)	


  print("WelcomeState init - finished")

end


function afterinit(cameraFree)

  print("WelcomeState afterinit - start")

  cameraFree:getCameraNode():setPosition(0, 500, 150)
	cameraFree:rotate(0,-45)
  print("WelcomeState afterinit - end")

end
