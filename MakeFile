all:
      g++ -std=c++17 ccurl.c -o ccurl

clean:
      $(RM) ccurl
