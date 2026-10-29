windows:
	clear
	echo "Starting cmake and first stage"
	cmake -P CmakeBuild.cmake

	echo "Starting make and second stage"
	
	gcc \
		build_stage_2/Main.cpp \
		build_stage_2/Renderer.cpp \
		build_stage_2/Input.cpp \
		build_stage_2/WAD/WAD.cpp \
		-fdiagnostics-color=always \
		-g \
		-static-libstdc++ \
		-fpermissive \
		-static-libgcc \
		-Wl,-Bstatic \
		-lstdc++ \
		-Wl,-Bdynamic \
		-static-libstdc++ \
		-Ibuild_stage_2/include/ \
		-ILibs/SDL3/include \
		-LLibs/SDL3/lib/x64 \
		-lSDL3 \
		-lSDL3_image \
		-o build/main.exe

clean:
	clear
	cmake -P CmakeClean.cmake