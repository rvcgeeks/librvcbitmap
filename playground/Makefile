all:
	g++-5 -Os contour_img.cpp -o rvc_contour_img_exec -lrvcbitmap
	g++-5 -Os mandelbrot.cpp -o rvc_mandelbrot_exec -lrvcbitmap
	g++-5 -Os differentiate.cpp -o rvc_differentiate_exec -lrvcbitmap
	g++-5 -Os wow.cpp -o rvc_wow_exec -lrvcbitmap
	g++-5 -Os L_system.cpp -o rvc_L_system_exec -lrvcbitmap
	g++-5 -Os rootfinder.cpp -o rvc_rootfinder_exec -lrvcbitmap
	./parallelize "./rvc_contour_img_exec" "./rvc_differentiate_exec rvcgeeks" "./rvc_wow_exec" "./rvc_L_system_exec" "./rvc_rootfinder_exec" 
	./rvc_mandelbrot_exec < mandelbrot_cmds.txt
	./rvc_mandelbrot_exec < julia_cmds.txt
	./rvc_mandelbrot_exec < glynn_cmds.txt
	mkdir gallery
	mv *.bmp gallery
	zip -9r rvcbitmap_exibition.zip gallery
	rm -rf gallery
clean:
	rm -f *.bmp rvc_*
