tick_len = 0.5  -- tick len in seconds 

function init()

  print("AISystem init - start")


  print("AISystem init - finished")

end


local targetPos = Vector3:new(0,0,0);

--local entity
--local aiComponent

function onTick( entity,aiComponent, body, phyiscsComp)
  
  --print("Lua.onTick");

  if not body.hasTargetPosition then
  
    targetPos = Vector3:new(math.random(-50 , 50),4.72,math.random(-50 , 50))
  
    --  AIEvents:moveToPosition(targetPos)
    aiComponent.targetPosition = targetPos;

    body:setTargetPosition(targetPos);
    phyiscsComp:get():setOrientation(body:getOrientation());
    
   -- entity.animationComponent:getParameter(3):setValue(1) -- 3 parameter for  baseanimation
      
    print(body.hasTargetPosition)
  
   
  end

 --print("targetPos -> x" .. targetPos.x .. "," .. targetPos.y .. "," .. targetPos.z)
 --print("AIBody.position -> x" .. AIBody.position.x .. "," .. AIBody.position.y .. "," .. AIBody.position.z)

--  print(body)

end