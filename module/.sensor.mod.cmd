savedcmd_sensor.mod := printf '%s\n'   sensor.o | awk '!x[$$0]++ { print("./"$$0) }' > sensor.mod
