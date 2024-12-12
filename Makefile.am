bin_PROGRAMS = FuncA HTTPserver
FuncA_SOURCES = main.cpp FuncA.cpp
check_PROGRAMS = test ServerTest
ServerTest_SOURCES = ServerTest.cpp
ServerTest_CPPFLAGS = -I/usr/include
ServerTest_LDADD = -lcurl
test_SOURCES = test.cpp FuncA.cpp
HTTPserver_SOURCES = HTTPserver.cpp FuncA.cpp

install-exec-hook:
	mkdir -p $(DESTDIR)/deb/DEBIAN
	echo "Package: sin-func" > $(DESTDIR)/deb/DEBIAN/control
	echo "Version: 1.0" >> $(DESTDIR)/deb/DEBIAN/control
	echo "Section: utils" >> $(DESTDIR)/deb/DEBIAN/control
	echo "Priority: optional" >> $(DESTDIR)/deb/DEBIAN/control
	echo "Architecture: any" >> $(DESTDIR)/deb/DEBIAN/control
	echo "Maintainer: Zorenko Dmytro zorenkodmytro03@gmail.com" >> $(DESTDIR)/deb/DEBIAN/control
	echo "Description: Calculate sin Function" >> $(DESTDIR)/deb/DEBIAN/control

EXTRA_DIST = Dockerfile
dockerfile:
	echo "FROM debian:bullseye-slim AS build" > Dockerfile
	echo "RUN apt-get update && apt-get install -y g++ make git" >> Dockerfile
	echo "WORKDIR /app" >> Dockerfile
	echo "RUN git clone https://github.com/DmytroZor/DevopsLabs1.git ." >> Dockerfile
	echo "RUN git checkout branchHTTTPserver" >> Dockerfile
	echo "RUN autoreconf -i && ./configure" >> Dockerfile
	echo "RUN make" >> Dockerfile
	echo "FROM alpine:latest" >> Dockerfile
	echo "RUN apk add --no-cache libstdc++" >> Dockerfile
	echo "COPY --from=build /app/HTTPserver /app/HTTPserver" >> Dockerfile
	echo "WORKDIR /app" >> Dockerfile
	echo "EXPOSE 8081" >> Dockerfile
	echo 'CMD ["./HTTPserver"]' >> Dockerfile
	 

all: dockerfile
