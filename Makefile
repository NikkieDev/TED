all: installer gui_app

installer:
	gcc ./cli/src/installer/*.c -o ./out/cli/TED_installer -I ./libs/curl -L"./libs/curl" -lcurl

gui_app:
	gcc ./gui/src/*.c -o ./out/gui/TED -mwindows

gui_d:
	gcc ./gui/src/*.c -o ./out/gui/TED

clean:
	rm ./out/cli/TED_installer.exe
