all:  make_installer

make_installer:
	gcc ./src/installer/*.c -o ../out/cli/TED_installer -I ../libs/installer/libs/curl -lcurl

clean:
	rm ../out/cli/TED_installer.exe