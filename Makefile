all:  make_installer

make_installer:
	gcc ./cli/src/installer/*.c -o ./out/cli/TED_installer -I ./libs/curl -L"./libs/curl" -lcurl

clean:
	rm ./out/cli/TED_installer.exe
