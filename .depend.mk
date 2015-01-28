object.o: object.cc object.h
player.o: player.cc player.h object.h bullet.h poof.h const.h
main.o: main.cc game.h asteroid.h object.h poof.h bullet.h player.h \
  gameState.h
game.o: game.cc game.h asteroid.h object.h poof.h bullet.h player.h \
  gameState.h const.h
gameState.o: gameState.cc gameState.h asteroid.h object.h poof.h bullet.h \
  player.h const.h
bullet.o: bullet.cc bullet.h object.h const.h
asteroid.o: asteroid.cc asteroid.h object.h poof.h bullet.h const.h
poof.o: poof.cc bullet.h object.h poof.h
