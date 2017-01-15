

function init(entity, cameraNode)

  print("CustomizeState init - start")

print("entity.bodyComponent.position -> x" .. entity.bodyComponent:getPosition().x .. "," .. entity.bodyComponent:getPosition().y .. "," .. entity.bodyComponent:getPosition().z)


--entity.physicsComponent:get():suspend(true)
entity.bodyComponent:setPosition(0.0,500.0,165.0)-- geht nicht! nur über phyiscsobject
--entity.physicsComponent:get():setPosition(0.0,350.0,0.0) -- wird von spawn überschrieben

cameraNode:setPosition(0.0,520.0,180.0)
 --local entityAI1 = XEngine.scene:createEntity(1, true)	
--local entityAI2 = XEngine.scene:createEntity(1, true)	

  print("CustomizeState init - finished")

end


function afterinit()

  print("CustomizeState afterinit - start")



  print("CustomizeState afterinit - end")

end
