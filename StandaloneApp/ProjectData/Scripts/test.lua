
posY 	= 0
delta 	= 0.001
counter = 0
posX 	= 0
posZ 	= 0

function update( )
	--do return end

	--log("hello bitch")
	posY = posY + delta

	if posY > 1 or posY < -1 then 
		delta = -delta
	end

	counter = counter + 0.01

	posZ = math.sin(counter) + 0.5

end



