testFile: creaturesTest mapTest
	./creaturesTest
	./mapTest

creaturesTest: ../Creatures.h ../Creatures.cpp ../PosDir.h ../posDir.cpp Tester.h Tester.cpp
	g++ creaturesTest.cpp ../Creatures.cpp ../posDir.cpp Tester.cpp -o creaturesTest

mapTest: ../Map.cpp ../Map.h ../PosDir.h ../posDir.cpp Tester.h Tester.cpp
	g++ mapTest.cpp ../Map.cpp ../posDir.cpp Tester.cpp -o mapTest

clean:
	rm mapTest creaturesTest
