all:
      g++ -std=c++17 main.c -o ccurl

clean:
      $(RM) ccurl
