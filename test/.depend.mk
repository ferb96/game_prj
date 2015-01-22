object.o: object.cc object.h
player.o: player.cc player.h object.h bullet.h object.cc
game.o: game.cc game.h
gameState.o: gameState.cc gameState.h asteroid.h player.h object.h \
 bullet.h object.cc
gameStateTest.o: gameStateTest.cc gameState.h asteroid.h player.h \
 object.h bullet.h object.cc
bullet.o: bullet.cc bullet.h object.cc object.h
