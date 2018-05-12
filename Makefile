all:ftp_client.run ftp_server.run

.PHONY : all
CFLAGS = -I.

ftp_client.run:ftp_client.cpp
	$(CXX) -o $@ $^ $(FLAGS)

ftp_server.run:ftp_server.o ftpd.o receive_and_save_file.o
	$(CXX) -o $@ $^ $(FLAGS)

ftpd.o:ftpd.cpp
	$(CXX) -c $^ $(FLAGS) -o $@

receive_and_save_file.o:receive_and_save_file.cpp
	$(CXX) -c $^ $(FLAGS)

.PHONY:clean
clean:
	-$(RM) ftp_client.run ftp_server.run ftp_server.o ftpd.o receive_and_save_file.o
