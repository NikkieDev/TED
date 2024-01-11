installer_win:
	gcc ./cli/src/installer/*.c -o ./out/cli/TED_installer -static-libgcc -lcurl -I ./libs/curl -L"./libs/curl"

installer_lin:
	gcc ./cli/src/installer/*.c -o ./out/cli/TED_installer -static-libgcc \
	&& g++ ./cli/src/server/*.cpp -o ./out/cli/server -static-libgcc

gui_app:
	gcc ./gui/src/*.c -o ./out/gui/TED -mwindows -static -static-libgcc

gui_d:
	gcc ./gui/src/*.c -o ./out/gui/TED -static -static-libgcc

clean:
	rm ./out/cli/TED_installer
	rm ./out/gui/TED
