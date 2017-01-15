
  
cam_height = 7    -- height of camera above character's center of mass
turn_speed = 1	-- turn speed of the character
zoom_speed = 1	-- camera zoom speed
walk_speed = 10  -- character walk speed in km/h

function onMoveFreeCamera(player)
--  player:
end

function onJoining(player)
--  player:
end
    
function update(entity, deltatime)
--  print("Playercontrollersystem  update")
--  print("Playercontrollersystem  update")
--    print("Playercontrollersystem  na endlich!!")
end

function doSpell(entity)
  
  print("doSpell")
  
 
end

function onPunch(entity)
  
  print("onPunch")
  
   entity.animationComponent:getParameter(3):setValue(1) -- 3 parameter for  baseanimation
   --entity.animationComponent:getParameter(7):setValue(1) -- 7 for top animation
   
end

function move(entity , direction)
  
  print("move")
end

function onMove()
  
  
end