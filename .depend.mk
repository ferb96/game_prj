object.o: object.cc object.h
player.o: player.cc player.h object.h bullet.h
collisionTest.o: collisionTest.cc player.h object.h bullet.h gameState.h \
  asteroid.h
gameState.o: gameState.cc gameState.h asteroid.h object.h player.h \
  bullet.h
bullet.o: bullet.cc bullet.h object.h
asteroid.o: asteroid.cc asteroid.h object.h
