bin_PROGRAMS = FuncA
FuncA_SOURCES = main.cpp FuncA.cpp

install-exec-hook:
	mkdir -p $(DESTDIR)/deb/DEBIAN
	echo "Package: sin-func" > $(DESTDIR)/deb/DEBIAN/control
	echo "Version: 1.0" >> $(DESTDIR)/deb/DEBIAN/control
	echo "Section: utils" >> $(DESTDIR)/deb/DEBIAN/control
	echo "Priority: optional" >> $(DESTDIR)/deb/DEBIAN/control
	echo "Architecture: any" >> $(DESTDIR)/deb/DEBIAN/control
	echo "Maintainer: Zorenko Dmytro zorenkodmytro03@gmail.com" >> $(DESTDIR)/deb/DEBIAN/control
	echo "Description: Calculate sin Function" >> $(DESTDIR)/deb/DEBIAN/control

