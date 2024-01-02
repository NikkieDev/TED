all: installer gui_app

installer:
	gcc ./cli/src/installer/*.c -o ./out/cli/TED_installer -static-libgcc -lcurl -I ./libs/curl -L"./libs/curl"

gui_app:
	gcc ./gui/src/*.c -o ./out/gui/TED -mwindows -static -static-libgcc

gui_d:
	gcc ./gui/src/*.c -o ./out/gui/TED

clean:
	rm ./out/cli/TED_installer.exe
	rm ./out/gui/TED.exe
