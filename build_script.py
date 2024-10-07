Import("env")

print (env.Dump())
       
platform = env.PioPlatform()
board = env.BoardConfig()
print(platform)
print(board)