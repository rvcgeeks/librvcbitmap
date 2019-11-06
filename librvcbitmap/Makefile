
	LDFLAGS    = -ffunction-sections -fno-rtti -fdata-sections -fno-common -fno-builtin -flto -Wl,--gc-sections 
	CXXFLAGS   = -Os -c -fPIC $(LDFLAGS) 
	STRIPFLAGS = --strip-all --discard-all -R .comment -R .gnu.version -R .note.*
	NAME       = rvcbitmap-dev_installer
	
all: librvcbitmap pack
	
librvcbitmap:
	$(CXX) $(CXXFLAGS) framework.cpp 
	$(CXX) $(CXXFLAGS) file_io.cpp 
	$(CXX) $(CXXFLAGS) utils.cpp 
	$(CXX) $(CXXFLAGS) shapes.cpp 
	$(CXX) -Os -shared $(LDFLAGS) framework.o file_io.o utils.o shapes.o -o librvcbitmap.so
	strip $(STRIPFLAGS) librvcbitmap.so
pack:
	mkdir $(NAME)
	mkdir $(NAME)/DEBIAN
	mkdir $(NAME)/usr
	mkdir $(NAME)/usr/lib
	mkdir $(NAME)/usr/include
	mv librvcbitmap.so $(NAME)/usr/lib
	cp *.h $(NAME)/usr/include
	cp control $(NAME)/DEBIAN
	dpkg-deb --build $(NAME)
	rm -r $(NAME)
	rm *.o
