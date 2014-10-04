LuaMashu = sgs.CreateDistanceSkill{
	name = "LuaMashu",
	correct_func = function(self, from, to)
		if from:hasSkill("LuaMashu") then
			return -1
		end
	end,
}
