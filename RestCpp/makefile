all:
	g++ -std=c++11 -I/usr/local/opt/openssl/include -c put.cpp
	g++ -stdlib=libc++ -lcpprest -lssl -lcrypto -lboost_system -lboost_thread-mt -lboost_chrono-mt  -o put put.o

clean:
	rm -rf put put.o
